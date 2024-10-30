#include "options.h"

int main(int argc, char** argv)
{
    int run_flag = 1;
    status_code status;
    String str;
    commands_codes cmd;
    Post post;
    Mail mail, *mail_ptr;
    int n;
    create_string(&str, NULL);

    while(1)
    {
        status = read_post(&post);
        if (!status) break;
        printf("%s", errors[status]);
    }
    printf("Success\n");
    while(run_flag)
    {
        printf("command: ");
        status = get_string(&str);
        if (status) break;
        cmd = identify_command(str);
        destruct_string(&str);
        status = OK;
        switch (cmd)
        {
            case add_mail_cmd:
                status = read_mail(&mail);
                if (status) break;
                if (post.mails_cnt == 0)
                {
                    mail_ptr = (Mail*) malloc(sizeof(Mail));
                }
                else
                {
                    mail_ptr = post.mails;
                    mail_ptr = (Mail*) realloc(post.mails, sizeof(Mail)*(post.mails_cnt + 1));
                }

                if (mail_ptr == NULL)
                {
                    status = MALLOC_ERROR;
                    break;
                }
                post.mails = mail_ptr;
                (post.mails)[post.mails_cnt] = mail;
                ++(post.mails_cnt);
                break;

            case delete_mail_cmd:
                printf("Mail ID (14 digits): ");
                status = get_id_string(&str, 14);
                if (status) break;
                status = delete_mail_from_post(&post, str);
                if (status) break;
                printf("The mail was removed\n");
                break;

            case search_mail_cmd:
                printf("Mail ID (14 digits): ");
                status = get_string(&str);
                if (status) break;
                status = search_mail(post, str, &n);
                if (status) break;
                print_mail_info(post.mails[n]);
                break;

            case all_mails_cmd:
                print_mail_tab(post.mails, post.mails_cnt);
                break;

            case deliver_cmd:
                printf("Mail ID (14 digits): ");
                status = get_string(&str);
                if (status) break;
                status = search_mail(post, str, &n);
                if (status) break;
                (post.mails)[n].is_delivered = 1;
                break;

            case delivered_cmd:
                printf("Delivered mails:\n");
                status = search_some_mails(post, 1, &mail_ptr, &n);
                if (status) break;
                print_mail_tab(mail_ptr, n);
                if (n != 0) free(mail_ptr);
                break;

            case expired_cmd:
                printf("Expired delivery mails:\n");
                status = search_some_mails(post, 0, &mail_ptr, &n);
                if (status) break;
                print_mail_tab(mail_ptr, n);
                if (n != 0) free(mail_ptr);
                break;

            case help:
                printf("Commands: %s", commands[0]);
                for (int i = 1; i < end; ++i)
                {
                    printf(", %s", commands[i]);
                }
                printf("\n");
                break;
            case exit_cmd:
                run_flag = 0;
                break;
            default:
                status = INVALID_INPUT;
                break;
        }
        printf("%s", errors[status]);
        if (str.length != 0) destruct_string(&str);
    }
    destruct_post(&post);
    printf("I always come back\n");
    return 0;
}