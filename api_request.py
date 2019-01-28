from lxml import html
import re
import psycopg2
from psycopg2.extras import DictCursor
import os
import asyncio
import aiohttp
import async_timeout
from urllib.parse import urljoin
from typing import *
from itertools import chain


async def fetch_classutil_page(session: aiohttp.ClientSession, page_url: str):
    with async_timeout.timeout(10):
        async with session.get(page_url) as response:
            response_bytes = await response.content.read()

    print("Fetched: {}".format(page_url))
    return response_bytes


async def main():
    pg_conn = psycopg2.connect(os.environ["DATABASE_URL"])
    pg_conn.set_session(autocommit=True)

    async with aiohttp.ClientSession() as session:
        index_urls = await fetch_classutil_index(session)

        tasks = []
        for page_url in index_urls:
            task = asyncio.ensure_future(fetch_classutil_page(session, page_url))
            tasks.append(task)
        responses = await asyncio.gather(*tasks)

        tasks = []
        for response in responses:
            task = asyncio.ensure_future(process_classutil_page(response))
            tasks.append(task)
        scrapes = await asyncio.gather(*tasks)  # Nested list of scrapes per page
        scrapes = list(chain.from_iterable(scrapes))  # Flatten

        await process_scrapes_batch(pg_conn, scrapes)

    pg_conn.close()


if __name__ == '__main__':
    # Note, that the loop here is a global loop
    # Thus, when you 'schedule' a task through ensure_future or similar,
    # it automatically assumes usage of this global loop.
    #
    # So, a 'task' represents a coroutine that's scheduled to execute eventually.
    # So a Future is similar to a Promise. The only difference being: A promise's lifecycle
    # and scheduling is handled by the Javascript engine; the Future's lifecycle and scheduling
    # is handled by this asyncio loop here.
    loop = asyncio.get_event_loop()
    loop.run_until_complete(main())
