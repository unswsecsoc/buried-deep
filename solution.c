/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    assert(l1 != NULL);
    assert(l2 != NULL); // Non-empty
    
    struct ListNode* r = NULL; // Result list
    struct ListNode* rn = NULL;
    
    int carry = 0;
    while (l1 != NULL || l2 != NULL || carry >= 1) {
        assert(carry == 0 || carry == 1);
        
        int l1_val = (l1 != NULL) ? l1->val : 0;
        int l2_val = (l2 != NULL) ? l2->val : 0; // Default digit is 0
        assert(l1_val >= 0 && l2_val >= 0);
        assert(l1_val <= 9 && l2_val <= 9);
        
        int compute = l1_val + l2_val + carry;
        carry = 0;
        assert(compute >= 0 && compute <= 9 + 9 + 1);
        
        if (compute >= 10) {
            carry = 1;
            compute = compute - 10; // Remove carried digit
        }
        // carry = (compute - 9) & 1u; // Peg to <=1
        // compute = compute - (10 * carry); // Remove carried digit
        assert(carry == 0 || carry == 1);
        assert(compute >= 0 && compute <= 9);
        
        struct ListNode *n = malloc(sizeof(struct ListNode));
        assert(n != NULL);
        
        n->val = compute;
        n->next = NULL;
        
        if (r != NULL) {
            rn->next = n;
            rn = n;
        } else {
            r = n;
            rn = n;
        }
        assert(r != NULL);
        assert(rn != NULL);
        assert(rn->next == NULL);
        
        if (l1 != NULL) l1 = l1->next;
        if (l2 != NULL) l2 = l2->next;
    }
    
    return r;
}
