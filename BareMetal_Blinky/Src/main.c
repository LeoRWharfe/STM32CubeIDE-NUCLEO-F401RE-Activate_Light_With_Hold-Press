#include <stdint.h>

int main(void) {
    // 1. Hardware Register Pointers

    // The Master Clock Control Register (Used for both Ports A and C)
    uint32_t *pRCC_AHB1ENR = (uint32_t *)0x40023830;

    // Port A (LED) Registers
    uint32_t *pGPIOA_MODER = (uint32_t *)0x40020000;
    uint32_t *pGPIOA_ODR   = (uint32_t *)0x40020014;

    // Port C (Button) Registers
    uint32_t *pGPIOC_MODER = (uint32_t *)0x40020800; // Corrected from 0x810 to 0x800
    uint32_t *pGPIOC_IDR   = (uint32_t *)0x40020810;


    // 2. Turn on Clock Gates for BOTH Port A and Port C
    *pRCC_AHB1ENR |= (1 << 0); // Enable Port A Clock (Bit 0)
    *pRCC_AHB1ENR |= (1 << 2); // Enable Port C Clock (Bit 2) - Corrected!


    // 3. Configure Roles
    // PA5 as Output (Bits 11:10 = 01)
    *pGPIOA_MODER &= ~(1 << 11);
    *pGPIOA_MODER |= (1 << 10);

    // PC13 as Input (Bits 27:26 = 00) - Perfect job here!
    *pGPIOC_MODER &= ~(1 << 27);
    *pGPIOC_MODER &= ~(1 << 26);


    // 4. The Infinite Interactive Loop
    while(1) {
        // We isolate Bit 13 using & (1 << 13).
        // If the result is 0, it means the pin is grounded (Button IS pressed)
        if ((*pGPIOC_IDR & (1 << 13)) == 0) {

            *pGPIOA_ODR |= (1 << 5);  // Turn LED on

        } else { // If the result is NOT 0, the pin is 3.3V (Button is NOT pressed)

            *pGPIOA_ODR &= ~(1 << 5); // Turn LED off
        }
    }
}
