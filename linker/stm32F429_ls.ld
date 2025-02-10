ENTRY(Reset_Handler)

MEMORY
{

    FLASH(rx) : ORIGIN = 0x08000000, LENGTH = 2048K
    SRAM(rw): ORIGIN = 0x20000000, LENGTH = 192K

}

PHDRS
{
    text PT_LOAD FLAGS(5);  /* Read (4) | Execute (1) = 5 */
    data PT_LOAD FLAGS(6);  /* Read (4) | Write (2) = 6 */
    bss PT_LOAD FLAGS(6);   /* Read (4) | Write (2) = 6 */
}

SECTIONS
{
  .isr_vector :
  {
    KEEP(*(.isr_vector))
  } >FLASH

  .text :
  {
    . = ALIGN(4);
		
    *(.text)
    *(.rodata)
		
    . = ALIGN(4);
    _etext = .;
  } >FLASH : text

  .data :
  {
    . = ALIGN(4);
    _sdata = .;
		
    *(.data)

    . = ALIGN(4);
    _edata = .;
  } >SRAM AT> FLASH

  .bss :
  {
    . = ALIGN(4);
    _sbss = .;
		
    *(.bss)
		
    . = ALIGN(4);
    _ebss = .;
  } >SRAM
}