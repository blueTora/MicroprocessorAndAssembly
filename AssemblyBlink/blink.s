PIO_PER equ  0x400E0E00	
PIO_SODR equ 0x400E0E30
PIO_CODR equ 0x400E0E34
PIO_OER equ  0x400E0E10 
PIO_PDSR equ 0x400E0E3C
PIO_ISR equ  0x400E0E4C
		
		area mycode, code, readonly
		export __main
		entry

__main
	bl led_1
	bl led_2
	bl led_3
	
connect_button
	ldr r1, =PIO_ISR
	ldr r2, [r1]
	cmp r2,#2_100000
	beq loop
	b connect_button
	
disconnect_button
	bl led1_off
	bl led2_off
	bl led3_off
	b connect_button

loop
	ldr r1, =PIO_ISR
	ldr r2, [r1]
	cmp r2, #2_1000000
	beq disconnect_button
	
	bl led1_on
	bl led2_on
	bl led3_on 
	
		bl delay
	
	bl led1_off
	
		bl delay
	
	bl led1_on
	
		bl delay
	
	bl led1_off
	bl led2_off
	
		bl delay
	
	bl led1_on
	
		bl delay
	
	bl led1_off
	
		bl delay
		
	bl led1_on
	bl led2_on
	bl led3_off
	
		bl delay
		
	bl led1_off
	
		bl delay
		
	bl led1_on
	
		bl delay
		
	bl led1_off
	bl led2_off
		
		bl delay
		
	bl led1_on
	
		bl delay
		
	bl led1_off
	
		bl delay
		
	bl led1_on
	bl led2_on
	bl led3_on
	
		bl delay
		
	bl loop
s
led_1

	mov r4, #2_1
	
	ldr r5,=PIO_PER
	str r4, [r5]
	
	ldr r5,=PIO_OER
	str r4, [r5]
	
	bx lr
	
led_2
	mov r4, #2_10
	
	ldr r5,=PIO_PER
	str r4, [r5]
	
	ldr r5,=PIO_OER
	str r4, [r5]
	
	bx lr
	
led_3
	mov r4, #2_100
	
	ldr r5,=PIO_PER
	str r4, [r5]
	
	ldr r5,=PIO_OER
	str r4, [r5]
	
	bx lr
	
led1_on
	mov r4, #2_1
	
	ldr r5,=PIO_SODR
	str r4, [r5]
	
	bx lr
	
led2_on
	mov r4, #2_10
	
	ldr r5,=PIO_SODR
	str r4, [r5]
	
	bx lr
	
led3_on
	mov r4, #2_100
	
	ldr r5,=PIO_SODR
	str r4, [r5]
	
	bx lr
	
led1_off
	mov r4, #2_1
	
	ldr r5,=PIO_CODR
	str r4, [r5]
	
	bx lr
	
led2_off
	mov r4, #2_10
	
	ldr r5,=PIO_CODR
	str r4, [r5]
	
	bx lr

led3_off
	mov r4, #2_100
	
	ldr r5,=PIO_CODR
	str r4, [r5]
	
	bx lr
	
delay
	mov r4, #0
	ldr r5, =0x00B0000
	
delay_loop
	ADD r4,r4,#1
	
	cmp r4,r5
	bne delay_loop
	
	bx lr
	
	end
		
