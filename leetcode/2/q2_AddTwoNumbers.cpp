class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

        ListNode*iter = NULL;
        ListNode *record = NULL;

        do{
            int num1 = 0;
            int num2 = 0;
            if(l1 != NULL)num1 = l1->val;
            if(l2 != NULL)num2 = l2->val;

            ListNode *l = new ListNode(num1 + num2);
            if(iter != NULL)iter -> next = l;
            else record = l;

            iter = l;

            if(l1 != NULL)l1 = l1 -> next;
            if(l2 != NULL)l2 = l2 -> next;
        }while(l1 != NULL || l2 != NULL);


        iter = record;
        do{
            if(iter -> val >= 10){
                iter -> val -= 10;
                if(iter -> next != NULL){
                    (iter -> next -> val)++;
                }
                else{
                    (iter -> next) = new ListNode(1);
                }
            }

            iter = iter->next;
        }while(iter != NULL);
        return record;


    }
};
