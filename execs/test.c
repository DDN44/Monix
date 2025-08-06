typedef struct functp{
    void (*sprint)(unsigned char *str);
}__attribute__((packed)) functp_t;

functp_t *pnt = 0;

int main()
{
    pnt->sprint("Hello from test exec\n");
    return 0;
}