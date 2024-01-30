	.cpu arm7tdmi
	.arch armv4t
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"USART.c"
	.text
	.align	2
	.global	USART_EnableClock
	.syntax unified
	.arm
	.type	USART_EnableClock, %function
USART_EnableClock:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #12
	str	r0, [fp, #-8]
	ldr	r3, [fp, #-8]
	ldr	r2, .L6
	cmp	r3, r2
	bne	.L2
	ldr	r3, .L6+4
	ldr	r3, [r3, #24]
	ldr	r2, .L6+4
	orr	r3, r3, #16384
	str	r3, [r2, #24]
	b	.L5
.L2:
	ldr	r3, [fp, #-8]
	ldr	r2, .L6+8
	cmp	r3, r2
	bne	.L4
	ldr	r3, .L6+4
	ldr	r3, [r3, #28]
	ldr	r2, .L6+4
	orr	r3, r3, #131072
	str	r3, [r2, #28]
	b	.L5
.L4:
	ldr	r3, [fp, #-8]
	ldr	r2, .L6+12
	cmp	r3, r2
	bne	.L5
	ldr	r3, .L6+4
	ldr	r3, [r3, #28]
	ldr	r2, .L6+4
	orr	r3, r3, #262144
	str	r3, [r2, #28]
.L5:
	nop
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
.L7:
	.align	2
.L6:
	.word	1073821696
	.word	1073876992
	.word	1073759232
	.word	1073760256
	.size	USART_EnableClock, .-USART_EnableClock
	.align	2
	.global	USART_EnablePeripheral
	.syntax unified
	.arm
	.type	USART_EnablePeripheral, %function
USART_EnablePeripheral:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #12
	str	r0, [fp, #-8]
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #12]
	orr	r2, r3, #8192
	ldr	r3, [fp, #-8]
	str	r2, [r3, #12]
	nop
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
	.size	USART_EnablePeripheral, .-USART_EnablePeripheral
	.align	2
	.global	USART_ConfigStopBits
	.syntax unified
	.arm
	.type	USART_ConfigStopBits, %function
USART_ConfigStopBits:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #12
	str	r0, [fp, #-8]
	mov	r3, r1
	strb	r3, [fp, #-9]
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #16]
	bic	r2, r3, #12288
	ldr	r3, [fp, #-8]
	str	r2, [r3, #16]
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #16]
	ldrb	r2, [fp, #-9]	@ zero_extendqisi2
	lsl	r2, r2, #12
	orr	r2, r3, r2
	ldr	r3, [fp, #-8]
	str	r2, [r3, #16]
	nop
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
	.size	USART_ConfigStopBits, .-USART_ConfigStopBits
	.align	2
	.global	USART_ConfigWordLength
	.syntax unified
	.arm
	.type	USART_ConfigWordLength, %function
USART_ConfigWordLength:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #12
	str	r0, [fp, #-8]
	mov	r3, r1
	strb	r3, [fp, #-9]
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #12]
	bic	r2, r3, #4096
	ldr	r3, [fp, #-8]
	str	r2, [r3, #12]
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #12]
	ldrb	r2, [fp, #-9]	@ zero_extendqisi2
	lsl	r2, r2, #12
	orr	r2, r3, r2
	ldr	r3, [fp, #-8]
	str	r2, [r3, #12]
	nop
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
	.size	USART_ConfigWordLength, .-USART_ConfigWordLength
	.align	2
	.global	USART_ConfigBaudrate
	.syntax unified
	.arm
	.type	USART_ConfigBaudrate, %function
USART_ConfigBaudrate:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #12
	str	r0, [fp, #-8]
	mov	r3, r1
	strb	r3, [fp, #-9]
	ldr	r3, [fp, #-8]
	ldr	r2, .L32
	cmp	r3, r2
	bne	.L12
	ldrb	r3, [fp, #-9]	@ zero_extendqisi2
	cmp	r3, #3
	ldrls	pc, [pc, r3, asl #2]
	b	.L28
.L15:
	.word	.L18
	.word	.L17
	.word	.L16
	.word	.L14
.L18:
	ldr	r3, [fp, #-8]
	ldr	r2, .L32+4
	str	r2, [r3, #8]
	b	.L20
.L17:
	ldr	r3, [fp, #-8]
	ldr	r2, .L32+8
	str	r2, [r3, #8]
	b	.L20
.L16:
	ldr	r3, [fp, #-8]
	ldr	r2, .L32+12
	str	r2, [r3, #8]
	b	.L20
.L14:
	ldr	r3, [fp, #-8]
	ldr	r2, .L32+16
	str	r2, [r3, #8]
	b	.L20
.L12:
	ldr	r3, [fp, #-8]
	ldr	r2, .L32+20
	cmp	r3, r2
	beq	.L21
	ldr	r3, [fp, #-8]
	ldr	r2, .L32+24
	cmp	r3, r2
	bne	.L29
.L21:
	ldrb	r3, [fp, #-9]	@ zero_extendqisi2
	cmp	r3, #3
	ldrls	pc, [pc, r3, asl #2]
	b	.L30
.L24:
	.word	.L27
	.word	.L26
	.word	.L25
	.word	.L23
.L27:
	ldr	r3, [fp, #-8]
	ldr	r2, .L32+8
	str	r2, [r3, #8]
	b	.L20
.L26:
	ldr	r3, [fp, #-8]
	ldr	r2, .L32+28
	str	r2, [r3, #8]
	b	.L20
.L25:
	ldr	r3, [fp, #-8]
	ldr	r2, .L32+16
	str	r2, [r3, #8]
	b	.L20
.L23:
	ldr	r3, [fp, #-8]
	mov	r2, #312
	str	r2, [r3, #8]
	b	.L20
.L28:
	nop
	b	.L31
.L29:
	nop
	b	.L31
.L30:
	nop
.L20:
.L31:
	nop
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
.L33:
	.align	2
.L32:
	.word	1073821696
	.word	7500
	.word	3750
	.word	1250
	.word	625
	.word	1073759232
	.word	1073760256
	.word	1875
	.size	USART_ConfigBaudrate, .-USART_ConfigBaudrate
	.align	2
	.global	USART_TransmitterEnable
	.syntax unified
	.arm
	.type	USART_TransmitterEnable, %function
USART_TransmitterEnable:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #12
	str	r0, [fp, #-8]
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #12]
	orr	r2, r3, #8
	ldr	r3, [fp, #-8]
	str	r2, [r3, #12]
	nop
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
	.size	USART_TransmitterEnable, .-USART_TransmitterEnable
	.align	2
	.global	USART_TransmitterDisable
	.syntax unified
	.arm
	.type	USART_TransmitterDisable, %function
USART_TransmitterDisable:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #12
	str	r0, [fp, #-8]
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #12]
	bic	r2, r3, #8
	ldr	r3, [fp, #-8]
	str	r2, [r3, #12]
	nop
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
	.size	USART_TransmitterDisable, .-USART_TransmitterDisable
	.align	2
	.global	USART_IOInit
	.syntax unified
	.arm
	.type	USART_IOInit, %function
USART_IOInit:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #8
	str	r0, [fp, #-8]
	ldr	r3, [fp, #-8]
	ldr	r2, .L39
	cmp	r3, r2
	bne	.L38
	mov	r2, #2
	mov	r1, #9
	mov	r0, #2
	bl	GPIO_Init
	mov	r2, #1
	mov	r1, #10
	mov	r0, #2
	bl	GPIO_Init
.L38:
	nop
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, lr}
	bx	lr
.L40:
	.align	2
.L39:
	.word	1073821696
	.size	USART_IOInit, .-USART_IOInit
	.align	2
	.global	USART_ReceiverEnable
	.syntax unified
	.arm
	.type	USART_ReceiverEnable, %function
USART_ReceiverEnable:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #12
	str	r0, [fp, #-8]
	ldr	r3, [fp, #-8]
	ldr	r3, [r3, #12]
	orr	r2, r3, #4
	ldr	r3, [fp, #-8]
	str	r2, [r3, #12]
	nop
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
	.size	USART_ReceiverEnable, .-USART_ReceiverEnable
	.align	2
	.global	USART_Init
	.syntax unified
	.arm
	.type	USART_Init, %function
USART_Init:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #8
	str	r0, [fp, #-8]
	mov	r0, r1
	mov	r1, r2
	mov	r2, r3
	mov	r3, r0
	strb	r3, [fp, #-9]
	mov	r3, r1
	strb	r3, [fp, #-10]
	mov	r3, r2
	strb	r3, [fp, #-11]
	ldr	r0, [fp, #-8]
	bl	USART_EnableClock
	ldr	r0, [fp, #-8]
	bl	USART_EnablePeripheral
	ldr	r0, [fp, #-8]
	bl	USART_IOInit
	ldrb	r3, [fp, #-9]	@ zero_extendqisi2
	mov	r1, r3
	ldr	r0, [fp, #-8]
	bl	USART_ConfigWordLength
	ldrb	r3, [fp, #-10]	@ zero_extendqisi2
	mov	r1, r3
	ldr	r0, [fp, #-8]
	bl	USART_ConfigStopBits
	ldrb	r3, [fp, #-11]	@ zero_extendqisi2
	mov	r1, r3
	ldr	r0, [fp, #-8]
	bl	USART_ConfigBaudrate
	nop
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, lr}
	bx	lr
	.size	USART_Init, .-USART_Init
	.align	2
	.global	USART_TransmitData
	.syntax unified
	.arm
	.type	USART_TransmitData, %function
USART_TransmitData:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #24
	str	r0, [fp, #-16]
	str	r1, [fp, #-20]
	mov	r3, r2
	strh	r3, [fp, #-22]	@ movhi
	ldr	r0, [fp, #-16]
	bl	USART_TransmitterEnable
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L44
.L46:
	ldr	r3, [fp, #-8]
	ldr	r2, [fp, #-20]
	add	r3, r2, r3
	ldrb	r3, [r3]	@ zero_extendqisi2
	mov	r2, r3
	ldr	r3, [fp, #-16]
	str	r2, [r3, #4]
	nop
.L45:
	ldr	r3, [fp, #-16]
	ldr	r3, [r3]
	and	r3, r3, #128
	cmp	r3, #0
	beq	.L45
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L44:
	ldrh	r3, [fp, #-22]
	ldr	r2, [fp, #-8]
	cmp	r2, r3
	blt	.L46
	nop
.L47:
	ldr	r3, [fp, #-16]
	ldr	r3, [r3]
	and	r3, r3, #128
	cmp	r3, #0
	beq	.L47
	ldr	r3, [fp, #-16]
	ldr	r3, [r3]
	bic	r2, r3, #128
	ldr	r3, [fp, #-16]
	str	r2, [r3]
	nop
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, lr}
	bx	lr
	.size	USART_TransmitData, .-USART_TransmitData
	.align	2
	.global	USART_ReceiveData
	.syntax unified
	.arm
	.type	USART_ReceiveData, %function
USART_ReceiveData:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #16
	str	r0, [fp, #-8]
	str	r1, [fp, #-12]
	mov	r3, r2
	strb	r3, [fp, #-13]
	ldr	r0, [fp, #-8]
	bl	USART_ReceiverEnable
	ldr	r3, [fp, #-8]
	ldr	r3, [r3]
	and	r3, r3, #32
	cmp	r3, #0
	beq	.L49
	ldr	r3, [fp, #-8]
	ldr	r2, [r3, #4]
	ldr	r3, .L52
	ldrb	r3, [r3]
	and	r3, r3, #255
	mov	r1, r3
	ldr	r3, [fp, #-12]
	add	r3, r3, r1
	and	r2, r2, #255
	strb	r2, [r3]
	ldr	r3, .L52
	ldrb	r3, [r3]
	and	r3, r3, #255
	add	r3, r3, #1
	and	r2, r3, #255
	ldr	r3, .L52
	strb	r2, [r3]
.L49:
	ldr	r3, .L52
	ldrb	r3, [r3]
	and	r3, r3, #255
	ldrb	r2, [fp, #-13]	@ zero_extendqisi2
	cmp	r2, r3
	bhi	.L51
	ldr	r3, .L52
	mov	r2, #0
	strb	r2, [r3]
.L51:
	nop
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, lr}
	bx	lr
.L53:
	.align	2
.L52:
	.word	UARTDataCount.0
	.size	USART_ReceiveData, .-USART_ReceiveData
	.bss
UARTDataCount.0:
	.space	1
	.size	UARTDataCount.0, 1
	.ident	"GCC: (GNU Arm Embedded Toolchain 10.3-2021.10) 10.3.1 20210824 (release)"
