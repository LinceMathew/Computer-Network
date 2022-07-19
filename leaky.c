#include <stdio.h>
void main()
{
    int bucket_size, outgoing_rate, no_of_packets, i, packet_size, buffer = 0, dropped_size;

    printf("enter the bucket size");
    scanf("%d", &bucket_size);
    printf("enter the outgoing rate");
    scanf("%d", &outgoing_rate);
    printf("enter the packet number");
    scanf("%d", &no_of_packets);
    for (i = 0; i < no_of_packets; i++)
    {
        printf("enter incoming packet : ");
        scanf("%d", &packet_size);
        if (buffer + packet_size <= bucket_size)
        {
            dropped_size = 0;
            buffer = buffer + packet_size;
        }
        else
        {
            dropped_size = packet_size - (bucket_size - buffer);
            buffer = bucket_size;
        }
        printf("Dropped packets\t:%d\nBuffer size \t:%d\nAfter outgoing\t:", dropped_size, buffer);
        if (buffer > outgoing_rate)
            buffer = buffer - outgoing_rate;
        else
            buffer = 0;
        printf("%d\n", buffer);
    }
}