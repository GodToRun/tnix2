void puts(char *a) {
    int ret;
    asm volatile("int $0x80" : "=a" (ret) : "0" (0), "b" ((int)a));
}
void schedule() {

}