import hash

block_a = hash.sha1("IV")
block_b = hash.sha1(a)
block_c = hash.sha1(b)
block_d = hash.sha1(c)
block_e = hash.sha1(d)

# Chain of block hashes

print(e);
