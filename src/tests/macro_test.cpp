#include <iostream>

#define RG_FUNC(name) __raygen__ ## name
#define IS_FUNC(name) __intersection__ ## name
#define AH_FUNC(name) __anyhit__ ## name
#define CH_FUNC(name) __closesthit__ ## name
#define MS_FUNC(name) __miss__ ## name
#define EX_FUNC(name) __exception__ ## name
#define DC_FUNC(name) __direct_callable__ ## name
#define CC_FUNC(name) __continuation_callable__ ## name

#define RG_FUNC_STR(name) "__raygen__" name
#define IS_FUNC_STR(name) "__intersection__" name
#define AH_FUNC_STR(name) "__anyhit__" name
#define CH_FUNC_STR(name) "__closesthit__" name
#define MS_FUNC_STR(name) "__miss__" name
#define EX_FUNC_STR(name) "__exception__" name
#define DC_FUNC_STR(name) "__direct_callable__" name
#define CC_FUNC_STR(name) "__continuation_callable__" name

void RG_FUNC(hoge)() {
    std::cout << "hoge" << std::endl;
}

int main() {
    RG_FUNC(hoge)();
    __raygen__hoge();
    return 0;
}