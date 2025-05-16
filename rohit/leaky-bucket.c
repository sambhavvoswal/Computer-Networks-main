#include<stdio.h>
#include<stdlib.h>

int main()
{
    int bs, or, np;
    printf("Enter bucket size: ");
    scanf("%d", &bs);
    
    printf("Enter output rate: ");
    scanf("%d", &or);
    
    printf("Enter number of packets: ");
    scanf("%d", &np);
    
    int a[np];
    printf("Enter the sizes of the packets:\n");
    for (int i = 0; i < np; i++) {
        scanf("%d", &a[i]);
    }
    
    int bc = 0;
    
    for (int i = 0; i < np; i++) {
        printf("\nProcessing packet %d of size %d...\n", i + 1, a[i]);
        
        if (a[i] > bs) {
            printf("Packet %d dropped (exceeds bucket size).\n", i + 1);
        } else {
            if (bc + a[i] < bs) {
                bc += a[i];
                printf("Packet %d added to the bucket. Current bucket content: %d\n", i + 1, bc);
            } else {
                printf("Packet %d dropped (bucket overflow).\n", i + 1);
            }
        }
        
        if (bc > 0) {
            int transmitted = (bc <= or) ? bc : or;
            bc -= transmitted;
            printf("output %d units. Remaining bucket content: %d\n", transmitted, bc);
        }
    }
    
    while (bc > 0) {
        printf("\n output remaining data\n");
        int transmitted = (bc <= or) ? bc : or;
        bc -= transmitted;
        printf("Transmitted %d units. Remaining bucket content: %d\n", transmitted, bc);
    }
    
    printf("\nAll a processed and bucket emptied.\n");
    return 0;
}