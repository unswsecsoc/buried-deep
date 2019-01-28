
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
