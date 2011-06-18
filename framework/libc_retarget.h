#ifndef _LIBC_RETARGET_H_
#define _LIBC_RETARGET_H_

/* Includes ---------------------------------------------------------------- */
/* Exported types ---------------------------------------------------------- */
/* Exported variables ------------------------------------------------------ */
/* Exported constants ------------------------------------------------------ */
/* Exported macro ---------------------------------------------------------- */
/* Exported functions ------------------------------------------------------ */

#ifdef __GNUC__

/* With GCC/RAISONANCE, small printf 
 * (option LD Linker->Libraries->Small printf set to 'Yes') 
 * calls __io_putchar() */

#define PUTCHAR_PROTOTYPE int __io_putchar(uint8 ch)
/*#define GETCHAT_PROTOTYPE int __io_getchar()*/
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
/*#define GETCHAR_PROTOTYPE int fgetc(FILE *f)*/
#endif /* __GNUC__ */

#endif /* _LIBC_RETARGET_H_ */
