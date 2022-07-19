#include <stdio.h>
int main()
{
    int Bucket_size, outgoing_rate, incoming_packet_size, no_of_packet, i, buffer = 0, dropped_size;
    printf("Enter the bucket size :\n");
    scanf("%d", &Bucket_size);
    printf("Outgoing packet rate :\n");
    scanf("%d", &outgoing_rate);
    printf("No. of packets :\n");
    scanf("%d", &no_of_packet);

    for (i = 0; i < no_of_packet; i++)
    {
        printf("\nEnter incoming packet size : ");
        scanf("%d", &incoming_packet_size);
        if (buffer + incoming_packet_size <= Bucket_size)
        {
            buffer += incoming_packet_size;
            dropped_size = 0;
        }
        else
        {
            dropped_size = incoming_packet_size - (Bucket_size - buffer);
            buffer = Bucket_size;
        }
        printf("Dropped packets\t: %d\nBuffer size\t: %d\nAfter outgoing\t: ", dropped_size, buffer);
        if (buffer > outgoing_rate)
            buffer -= outgoing_rate;
        else
            buffer = 0;
        printf("%d\n", buffer);
    }
    return 0;
}
