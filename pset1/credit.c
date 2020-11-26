#include <cs50.h>
#include <stdio.h>

#define MAX_CC_DIGITS 16
#define LOW_VALID_NUMBER 999999999999
#define HGH_VALID_NUMBER 10000000000000000

#define VISA_NUM_1 4
#define AMERICANEXPRESS_NUM_1 34
#define AMERICANEXPRESS_NUM_2 37
#define MASTERCARD_NUM_RANGE_MIN 51
#define MASTERCARD_NUM_RANGE_MAX 55

int split_digits(size_t num, int *dig_arr);
int double_n_split_digits(int *ipt_arr, int ipt_len, int *otp_arr);
int sum_digits(int *ipt_arr, int ipt_len, int *otp_arr, int otp_len);
int concat_int(int tens, int ones);

int main(void)
{
    size_t cn;

    do
    {
        cn = get_long("Number: ");
    }
    /* could also use <math.h> and the condition below, but decided to avoid an extra lib
     * while (cn < pow(10, MIN_CC_DIGITS) || cn >= pow(10, (MAX_CC_DIGITS + 1))) */
    while (cn <= LOW_VALID_NUMBER || cn >= HGH_VALID_NUMBER);
    
    /* cn = credit number, dn = doubled cn */
    int *cn_array = (int*) malloc(sizeof(int[MAX_CC_DIGITS]));
    int cn_arr_len = split_digits(cn, cn_array);
    
    int *dn_array = (int*) malloc(sizeof(int[MAX_CC_DIGITS * 2]));
    int dn_arr_len = double_n_split_digits(cn_array, cn_arr_len, dn_array);
    
    int sum = sum_digits(cn_array, cn_arr_len, dn_array, dn_arr_len);
    int first_two = concat_int(cn_array[cn_arr_len - 1], cn_array[cn_arr_len - 2]);

    /* free heap memory */
    free(cn_array);
    free(dn_array);

    /* check sum of doubled digits plus non-doubled if it ends in 0 */
    if (sum % 10 != 0)
    {
        printf("INVALID_SUM\n");
        return 1;
    }

    /* check for corporation's intial number */
    if (first_two / 10 == VISA_NUM_1)
    {
        printf("VISA\n");
    }
    else if (first_two == AMERICANEXPRESS_NUM_1 || first_two == AMERICANEXPRESS_NUM_2)
    {
        printf("AMEX\n");
    }
    else if (first_two >= MASTERCARD_NUM_RANGE_MIN && first_two <= MASTERCARD_NUM_RANGE_MAX)
    {
        printf("MASTERCARD\n");
    }
    else
    {
        /* could also be from an unsupported company */
        printf("INVALID_NAME\n");
        return 1;
    }

    return 0;
}

int split_digits(size_t num, int *dig_arr)
{
    int len;
    
    for (len = 0; num > 0; ++len)
    {
        /* remainder becomes next elem of array, digits are placed in reverse */
        int dig = num % 10;
        dig_arr[len] = dig;
        
        /* integer division by ten, ignoring remainder */
        num /= 10;
        printf("%d ", dig_arr[len]);
    }
    
    printf("[%d]\n", len);
    return len;
}

int double_n_split_digits(int *ipt_arr, int ipt_len, int *otp_arr)
{
    int *two_dig = (int*) malloc(sizeof(int[2]));
    int otp_len = 0;
    
    /* i leads the iterator through the input array, and output length grows with every double digit number */
    for (int i = 0; i < ipt_len; ++i, ++otp_len)
    {
        /* zeroing odd pos digits */
        if (i % 2 == 0)
        {
            otp_arr[otp_len] = 0;
            printf("%d ", otp_arr[otp_len]);
        }
        /* for digits doubled greater than 9, split them on output array */
        else if (ipt_arr[i] > 4)
        {
            printf("| ");
            split_digits(ipt_arr[i] * 2, two_dig);
            otp_arr[otp_len] = two_dig[0];
            otp_arr[otp_len + 1] = two_dig[1];
            
            printf("%d ", otp_arr[otp_len]);
             
            /* advances output index one extra step to accommodate two digits split */
            ++otp_len;
            printf("%d ", otp_arr[otp_len]);
        }
        /* simply double every other digit smaller than 5 */
        else
        {
            otp_arr[otp_len] = ipt_arr[i] * 2;
            printf("%d ", otp_arr[otp_len]);
        }
    }
    
    free(two_dig);
    
    printf("[%d]\n", otp_len);
    return otp_len;
}

int sum_digits(int *ipt_arr, int ipt_len, int *otp_arr, int otp_len)
{
    int sum = 0;
    
    /* adds digits that were not doubled */
    for (int i = 0; i < ipt_len; i += 2)
    {
        sum += ipt_arr[i];
        printf("%d ", ipt_arr[i]);
    }
    printf("[%d]\n", sum);
    
    /* adds the digits of the doubled from original array */
    for (int i = 0; i < otp_len; ++i)
    {
        sum += otp_arr[i];
        printf("%d ", otp_arr[i]);
    }
    printf("[%d]\n", sum);
    
    return sum;
}

int concat_int(int tens, int ones)
{
    return tens * 10 + ones;
}

