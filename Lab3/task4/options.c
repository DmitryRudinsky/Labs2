#include "options.h"

status_code create_string(String* str, char* s)
{
    if (str == NULL) return INVALID_PARAMS;
    if (s == NULL)
    {
        str->length = 0;
        str->head = NULL;
        return OK;
    }

    str->length = strlen(s);
    str->head = (char*) malloc(sizeof(char) * (str->length + 1));
    if (str->head == NULL)
    {
        return MALLOC_ERROR;
    }
    strcpy(str->head, s);
    return OK;
}

status_code string_insert(String* str, char c)
{
    char* tmp;
    if (str == NULL) return INVALID_PARAMS;
    tmp = (char*) malloc(sizeof(char)*(str->length + 2));
    if (tmp == NULL) return MALLOC_ERROR;
    for(int i = 0; i < str->length; ++i)
    {
        tmp[i] = (str->head)[i];
    }
    tmp[str->length] = c;
    tmp[str->length + 1] = '\0';
    free(str->head);
    str->head = tmp;
    ++(str->length);
    return OK;
}

status_code destruct_string(String* str)
{
    if (str == NULL) return INVALID_PARAMS;
    free(str->head);
    str->head = NULL;
    str->length = 0;
    return OK;
}

int compare_strings(const String str1, const String str2)
{
    if (str1.length != str2.length)
    {
        return str1.length < str2.length ? -1 : 1;
    }
    return strcmp(str1.head, str2.head);
}

int equal_strings(String left, String right)
{
    if (left.length != right.length) return 0;
    return !strcmp(left.head, right.head);
}

status_code copy_string(const String source, String* dest)
{
    char* tmp;
    if (dest == NULL) return INVALID_PARAMS;
    tmp = (char*) malloc(sizeof(char) * (source.length+1));
    if (tmp == NULL)
    {
        return MALLOC_ERROR;
    }
    dest->head = tmp;
    dest->length = source.length;
    strcpy(dest->head, source.head);
    return OK;
}

status_code new_copy_string(const String source, String** dest)
{
    if (dest == NULL) return INVALID_PARAMS;

    *dest = (String*) malloc(sizeof(String));
    if (*dest == NULL)
    {
        return MALLOC_ERROR;
    }
    return copy_string(source, *dest);
}

status_code concat_string(String* first, const String second)
{
    char* tmp;

    if (first == NULL) return INVALID_PARAMS;
    tmp = (char*) realloc(first->head, sizeof(char) * (second.length + first->length + 1));
    if (tmp == NULL)
    {
        return MALLOC_ERROR;
    }
    first->length = first->length + second.length;
    first->head = tmp;
    strcat(first->head, second.head);
    return OK;
}

void print_string(const String str)
{
    for(int i = 0; i < str.length; ++i)
    {
        printf("%c", (str.head)[i]);
    }
    printf("\n");
    return;
}

status_code destruct_address(Address* addr)
{
    if (addr == NULL) return INVALID_INPUT;

    destruct_string(&(addr->city));
    destruct_string(&(addr->street));
    destruct_string(&(addr->building));
    destruct_string(&(addr->receiver_id));
    addr->house_number = 0;
    addr->apartment_number = 0;
    return OK;
}

status_code destruct_mail(Mail* mail)
{
    if (mail == NULL)
    {
        return INVALID_INPUT;
    }
    destruct_address(&(mail->receiver_address));
    destruct_string(&(mail->mail_id));
    destruct_string(&(mail->creation_time));
    destruct_string(&(mail->delivery_time));
    mail->weight = 0;
    mail->is_delivered = 0;
    return OK;
}

status_code destruct_post(Post* post)
{
    if (post == NULL) return INVALID_PARAMS;

    destruct_address(&(post->office_addr));
    for (int i = 0; i < post->mails_cnt; ++i)
    {
        destruct_mail(post->mails + i);
    }
    if(post->mails_cnt) free(post->mails);
    post->mails_cnt = 0;
    return OK;
}

int mail_comparator(const void* l, const void* r)
{
    Mail* mail_l = (Mail*) l;
    Mail* mail_r = (Mail*) r;
    if (!equal_strings(mail_l->receiver_address.receiver_id, mail_r->receiver_address.receiver_id))
    {
        return compare_strings(mail_l->receiver_address.receiver_id, mail_r->receiver_address.receiver_id);
    }
    return compare_strings(mail_l->mail_id, mail_r->mail_id);
}

int mail_time_comparator(const void* l, const void* r)
{
    char l_time[10], r_time[10];
    Mail* mail_l = (Mail*) l;
    Mail* mail_r = (Mail*) r;
    int ans;
    for(int i = 0; i < 5; ++i)
    {
        l_time[i] = (mail_l->creation_time.head)[i+5];
        r_time[i] = (mail_r->creation_time.head)[i+5];
    }
    for(int i = 0; i < 5; ++i)
    {
        l_time[i+5] = (mail_l->creation_time.head)[i];
        r_time[i+5] = (mail_r->creation_time.head)[i];
    }
    ans = strcmp(l_time, r_time);
    if (!ans) return ans;
    return strcmp(mail_l->creation_time.head + 11, mail_r->creation_time.head + 11);
}

status_code search_mail(const Post post, const String mail_ID, int* ind)
{
    if (ind == NULL) return INVALID_PARAMS;
    if (mail_ID.length != 14) return INVALID_INPUT;
    for(int i = 0; i < mail_ID.length; ++i)
    {
        if((mail_ID.head)[i] < '0' || (mail_ID.head)[i] > '9')
        {
            return INVALID_ID;
        }
    }
    for (int i = 0; i < post.mails_cnt; ++i)
    {
        if (equal_strings(post.mails[i].mail_id, mail_ID))
        {
            *ind = i;
            return OK;
        }
    }
    return INVALID_ID;
}

status_code add_mail_to_post(Post* post, const Mail mail)
{
    int ind;
    Mail* tmp;
    if (post == NULL) return INVALID_INPUT;

    if (search_mail(*post, mail.mail_id, &ind) == OK)
    {
        return INVALID_ID;
    }
    ++(post->mails_cnt);
    tmp = (Mail*) realloc(post->mails, sizeof(Mail) * (post->mails_cnt));
    if (tmp == NULL) return MALLOC_ERROR;

    post->mails = tmp;

    (post->mails)[(post->mails_cnt)-1] = mail;
    qsort(post->mails, post->mails_cnt, sizeof(Mail), mail_comparator);
    return OK;
}

status_code delete_mail_from_post(Post* post, const String mail_ID)
{
    int ind;
    status_code status;
    Mail* tmp;
    if (post == NULL) return INVALID_INPUT;

    status = search_mail(*post, mail_ID, &ind);
    if (status) return status;

    destruct_mail((post->mails)+ind);
    for (int i = ind + 1; i < post->mails_cnt; ++i)
    {
        post->mails[i-1] = post->mails[i];
    }
    --(post->mails_cnt);
    tmp = realloc(post->mails, sizeof(Mail) * (post->mails_cnt));
    if (tmp == NULL)
    {
        return MALLOC_ERROR;
    }
    post->mails = tmp;
    return OK;
}

commands_codes identify_command(const String input)
{
    int matched;
    for (int i = 0; i < end; ++i)
    {
        matched = 1;
        for (int j = 0; j < input.length; ++j)
        {
            if ((input.head)[j] != commands[i][j])
            {
                matched = 0;
                break;
            }
        }
        if (matched) return i;
    }
    return -1;
}

status_code get_string(String* input)
{
    char c;
    status_code status;
    if (input == NULL) return INVALID_PARAMS;
    c = getchar();
    while(c != '\n')
    {
        status = string_insert(input, c);
        if(status)
        {
            destruct_string(input);
            return status;
        }
        c = getchar();
    }
    return OK;
}

status_code string_to_uint(const String str, int* n)
{
    char c;
    if (n == NULL) return INVALID_PARAMS;
    *n = 0;
    for(int i = 0; i < str.length; ++i)
    {
        c = (str.head)[i];
        if (c < '0' || c > '9') return INVALID_INPUT;
        if (INT_MAX / 10 - c + '0' < *n) return OVERFLOW;
        *n *= 10;
        *n += c - '0';
    }
    return OK;
}

status_code string_to_udouble(const String str, double* n)
{
    char c;
    int i;
    double after_dot;
    if (n == NULL) INVALID_PARAMS;
    *n = 0;
    for(i = 0; i < str.length; ++i)
    {
        c = (str.head)[i];
        if (c == '.') break;
        if (c < '0' || c > '9') return INVALID_INPUT;
        if (DBL_MAX / 10 - c + '0' < *n) return OVERFLOW;
        *n *= 10;
        *n += c - '0';
    }
    if (i == str.length) return OK;
    after_dot = 0;
    i = str.length - 1;
    c = (str.head)[i];
    for(; (str.head)[i] != '.' ; --i)
    {
        if (c < '0' || c > '9') return INVALID_INPUT;
        after_dot /= 10;
        after_dot += c - '0';
        c = (str.head)[i];
    }
    *n += after_dot / 10;
    return OK;
}

status_code get_time_string(String* str_time)
{
    char tmp[20];
    time_t cur_time;
    struct tm* cur_tm;
    if (str_time == NULL) return INVALID_PARAMS;
    cur_time = time(NULL);
    cur_tm = localtime(&cur_time);
    sprintf(tmp, "%02d:%02d:%04d %02d:%02d:%02d", cur_tm->tm_mday, cur_tm->tm_mon + 1,
            cur_tm->tm_year + 1900, cur_tm->tm_hour, cur_tm->tm_min, cur_tm->tm_sec);
    tmp[19] = '\0';
    return create_string(str_time, tmp);
}

status_code check_uint_format(const String str, const int digits)
{
    if (str.length != digits) return INVALID_INPUT;
    for (int i = 0; i < str.length; ++i)
    {
        if ((str.head)[i] < '0' || (str.head)[i] > '9') return INVALID_INPUT;
    }
    return OK;
}

status_code check_time_format(const String str_time)
{
    char c;
    int data[6];
    int i = 0, j = 0;
    if (str_time.length != 19 || (str_time.head)[10] != ' ') return INVALID_INPUT;
    for (; i < 10; ++i)
    {
        c = (str_time.head)[i];
        if (i == 2 || i == 5)
        {
            if (c != ':') return INVALID_INPUT;
            ++j;
            data[j] = 0;
            continue;
        }
        else if (c < '0' || c > '9') return INVALID_INPUT;
        data[j] *= 10;
        data[j] += c - '0';
    }
    if (data[0] != 0 && data[0] < 32 && data[1] != 0 && data[1] < 13)
    {
        switch (data[1])
        {
            case 2:
                if (data[2] % 400 == 0 || (data[2] % 100 != 0 && data[2] % 4 == 0))
                {
                    if (data[0] > 29) return INVALID_INPUT;
                }
                else if (data[0] > 28) return INVALID_INPUT;
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                if (data[0] == 31) return INVALID_INPUT;
            default:
                break;
        }
    }
    else return INVALID_INPUT;
    ++j;
    data[j] = 0;
    ++i;
    for (; i < str_time.length; ++i)
    {
        c = (str_time.head)[i];
        if (i == 13 || i == 16)
        {
            if (c != ':') return INVALID_INPUT;
            ++j;
            data[j] = 0;
            continue;
        }
        else if (c < '0' || c > '9') return INVALID_INPUT;
        data[j] *= 10;
        data[j] += c - '0';
    }
    if (data[3] > 23 || data[4] > 59 || data[5] > 59)
    {
        return INVALID_INPUT;
    }
    return OK;
}

status_code get_id_string(String* id, int len)
{
    status_code status = get_string(id);
    if (id == NULL) return INVALID_PARAMS;
    if (status) return status;
    return check_uint_format(*id, len);
}

status_code read_adress(Address* address)
{
    String str;
    status_code status;
    int n;
    if (address == NULL) return INVALID_PARAMS;

    create_string(&str, NULL);
    printf("City: ");
    status = get_string(&str);
    if (status) return status;
    if (str.length == 0) return INVALID_INPUT;
    address->city = str;
    str.head = NULL;
    str.length = 0;

    printf("Street: ");
    status = get_string(&str);
    if (status) return status;
    if (str.length == 0) return INVALID_INPUT;
    address->street = str;
    str.head = NULL;
    str.length = 0;

    printf("Building: ");
    status = get_string(&str);
    if (status) return status;
    if (str.length == 0) return INVALID_INPUT;
    address->building = str;
    str.head = NULL;
    str.length = 0;

    printf("House number: ");
    status = get_string(&str);
    if (status) return status;
    if (str.length == 0) return INVALID_INPUT;
    status = string_to_uint(str, &n);
    if (status) return status;
    address->house_number = n;
    str.head = NULL;
    str.length = 0;

    printf("Apartment number: ");
    status = get_string(&str);
    if (status) return status;
    if (str.length == 0) return INVALID_INPUT;
    status = string_to_uint(str, &n);
    if (status) return status;
    address->apartment_number = n;
    str.head = NULL;
    str.length = 0;

    printf("Receiver ID (6 digits): ");
    status = get_id_string(&str, 6);
    if (status) return status;
    if (str.length == 0) return INVALID_INPUT;
    address->receiver_id = str;
    str.head = NULL;
    str.length = 0;

    return OK;
}

status_code read_mail(Mail* mail)
{
    status_code status;
    String str;
    double n;
    if (mail == NULL) return INVALID_PARAMS;

    printf("Entering the receiver address:\n");
    status = read_adress(&(mail->receiver_address));
    if (status) return status;

    create_string(&str, NULL);
    printf("Mail ID (14 digits): ");
    status = get_id_string(&str, 14);
    if (status) return status;
    mail->mail_id = str;
    str.head = NULL;
    str.length = 0;

    printf("Delivery time (dd:MM:yyyy hh:mm:ss): ");
    status = get_string(&str);
    if (status) return status;
    status = check_time_format(str);
    if (status) return status;
    mail->delivery_time = str;
    str.head = NULL;
    str.length = 0;

    printf("Weight: ");
    status = get_string(&str);
    if (status) return status;
    if (str.length == 0) return INVALID_INPUT;
    status = string_to_udouble(str, &n);
    if (status) return status;
    mail->weight = n;
    str.head = NULL;
    str.length = 0;

    get_time_string(&str);
    mail->creation_time = str;
    mail->is_delivered = 0;
    return OK;
}

status_code read_post(Post* post)
{
    if (post == NULL) return INVALID_PARAMS;

    post->mails_cnt = 0;
    printf("Entering the post address:\n");
    return read_adress(&(post->office_addr));;
}

void print_mail_info(const Mail mail)
{
    printf("Receiver id: ");
    print_string(mail.receiver_address.receiver_id);

    printf("Receiver address:\n");
    printf("City: ");
    print_string(mail.receiver_address.city);
    printf("Street: ");
    print_string(mail.receiver_address.street);
    printf("Number of house: ");
    printf("%d\n", mail.receiver_address.house_number);
    printf("Building: ");
    print_string(mail.receiver_address.building);
    printf("Apartment: ");
    printf("%d\n", mail.receiver_address.apartment_number);

    printf("Mail weight: ");
    printf("%f\n", mail.weight);
    printf("Time of delivery: ");
    print_string(mail.delivery_time);
    printf("Created: ");
    print_string(mail.creation_time);
    printf("Status: ");
    if (mail.is_delivered) printf("Delivered\n");
    else printf("Not delivered\n");
    return;
}

status_code compare_time_with_cur(const String str_time, int* has_come)
{
    time_t cur_time;
    struct tm* loc_time;
    long tmp = 0;
    char* t = str_time.head;
    cur_time = time(NULL);
    loc_time = localtime(&cur_time);
    if (check_time_format(str_time)) return INVALID_PARAMS;
    for (int i = 6; i < 10; ++i)
    {
        tmp *= 10;
        tmp += t[i] - '0';
    }
    tmp -= 1900;
    if (tmp != loc_time->tm_year)
    {
        *has_come = tmp < loc_time->tm_year;
        return OK;
    }
    tmp = (t[3] - '0') * 10 + (t[4] - '0');
    tmp -= 1;
    if (tmp != loc_time->tm_mon)
    {
        *has_come = tmp < loc_time->tm_mon;
        return OK;
    }
    tmp = (t[0] - '0') * 10 + (t[1] - '0');
    if (tmp != loc_time->tm_mday)
    {
        *has_come = tmp < loc_time->tm_mday;
        return OK;
    }
    tmp = (t[11] - '0') * 10 + (t[12] - '0');
    if (tmp != loc_time->tm_hour)
    {
        *has_come = tmp < loc_time->tm_hour;
        return OK;
    }
    tmp = (t[14] - '0') * 10 + (t[15] - '0');
    if (tmp != loc_time->tm_min)
    {
        *has_come = tmp < loc_time->tm_min;
        return OK;
    }
    tmp = (t[17] - '0') * 10 + (t[18] - '0');
    if (tmp != loc_time->tm_sec)
    {
        *has_come = tmp < loc_time->tm_sec;
        return OK;
    }
    *has_come = 1;
    return OK;
}

status_code print_mail_tab(Mail* mails, int cnt)
{
    if (mails == NULL) return INVALID_PARAMS;
    if (cnt == 0)
    {
        printf("Nothing was found\n");
        return OK;
    }
    printf("| ReceiverID |     MailID     |  wght  |   time of creation  |  time of delivery   | Delivered |\n");
    for(int i = 0; i < cnt; ++i)
    {
        printf("| %10s | %s | % 3.2lf | %s | %s ",
               (mails[i]).receiver_address.receiver_id.head,
               (mails[i]).mail_id.head, (mails[i]).weight,
               (mails[i]).creation_time.head, (mails[i]).delivery_time.head);
        if ((mails)[i].is_delivered) printf("|       YES |");
        else printf("|        NO |");
        printf("\n");
    }
    printf("\n");
    return OK;
}

status_code search_some_mails(Post post, int delivered, Mail** ans, int* ans_len)
{
    if (ans == NULL || ans_len == NULL) return INVALID_INPUT;
    int expired;
    status_code status;
    *ans = (Mail*) malloc(sizeof(Mail)*(post.mails_cnt));
    if (*ans == NULL) return MALLOC_ERROR;
    *ans_len = 0;
    for (int i = 0; i < post.mails_cnt; ++i)
    {
        if((post.mails)[i].is_delivered == delivered)
        {
            if (delivered == 1)
            {
                (*ans)[*ans_len] = (post.mails)[i];
                ++(*ans_len);
                continue;
            }
            status = compare_time_with_cur((post.mails)[i].delivery_time, &expired);
            if (status)
            {
                free(*ans);
                return status;
            }
            if (!expired == delivered)
            {
                (*ans)[*ans_len] = (post.mails)[i];
                ++(*ans_len);
            }
        }
    }
    if (*ans_len == 0)
    {
        free(*ans);
        return OK;
    }
    *ans = (Mail*) realloc(*ans, sizeof(Mail)*(*ans_len));
    if (*ans == NULL) return MALLOC_ERROR;
    qsort(*ans, *ans_len, sizeof(Mail), mail_time_comparator);
    return OK;
}

