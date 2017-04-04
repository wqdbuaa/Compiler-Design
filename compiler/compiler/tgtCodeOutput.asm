.data	:	    	    
str0:	.asciiz	"->"	    
str1:	.asciiz	"\n"	    
str2:	.asciiz	"->"	    
str3:	.asciiz	"\n"	    
str4:	.asciiz	"before sort :"	    
str5:	.asciiz	" "	    
str6:	.asciiz	"after sort :"	    
str7:	.asciiz	" "	    
str8:	.asciiz	"\n"	    
str9:	.asciiz	"\n hanoi tower return how many times? "	    
str10:	.asciiz	"\n fib return how many times? "	    
str11:	.asciiz	"\n swap return how many times? "	    
str12:	.asciiz	"\n QuIcksORT tower return how many times? "	    
str13:	.asciiz	"\n----------------------------------------"	    
str14:	.asciiz	"\n not this value!!!!"	    
str15:	.asciiz	"\n not this value too!!!!"	    
str16:	.asciiz	"\n not this value too!!!!"	    
str17:	.asciiz	"\n Ok !!!"	    
str18:	.asciiz	"\n so be it."	    
str19:	.asciiz	"\n----------------------------------------"	    
str20:	.asciiz	"\n should not be output"	    
str21:	.asciiz	"\n----------------------------------------"	    
end_of_data: 

 .text: 
la $t9, end_of_data
div $t9 $t9 4
addi $t9 $t9 1
mul $t9 $t9 4
add $fp $0 $t9
# this is the beginning of the program
addi	$t0	$0	0
sw	$t0	0($t9)	    
addi	$fp	$t9	0
#	global int constant	    	    
addi	$t0	$0	1
sw	$t0	4($t9)	    
addi	$fp	$t9	4
#	global int constant	    	    
addi	$t0	$0	2
sw	$t0	8($t9)	    
addi	$fp	$t9	8
#	global int constant	    	    
addi	$t0	$0	3
sw	$t0	12($t9)	    
addi	$fp	$t9	12
#	global int constant	    	    
addi	$fp	$t9	16
addi	$fp	$fp	80
#	find array variable	s	    
addi	$fp	$t9	96
#	find variable	num_v1	    
addi	$fp	$t9	100
#	find variable	num_v2	    
addi	$fp	$t9	104
#	find variable	num_v3	    
addi	$fp	$t9	108
#	find variable	num_v4	    
addi	$fp	$t9	112
#	find variable	num_v5	    
j	main	    	    
fib	:	    	    
addu	$fp	$fp	$t8
sw	$t8	-12($fp)	    
sw	$ra	-4($fp)	    
#	fib function zone	    	    
lw	$a0	0($sp)	    
sw	$a0	0($fp)	    
#	parameter manipulation	    	    
lw	$t0	0($fp)	    
li	$t1	1	    
bge	$t0	$t1	Lab0
#	logical judgement	bge	    
lw	$t0	100($t9)	    
li	$t1	1	    
addu	$t2	$t0	$t1
sw	$t2	4($fp)	    
#	addu	    	    
lw	$t0	4($fp)	    
sw	$t0	100($t9)	    
#	assignment sentence	    	    
li	$t0	-1	    
#	get the return value immediate number	    	    
sw	$t0	-8($fp)	    
#	save the value in the running stack	    	    
lw	$t8	-12($fp)	    
lw	$ra	-4($fp)	    
jr	$ra	    	    
#	jump back	    	    
Lab0	:	    	    
lw	$t0	0($fp)	    
li	$t1	1	    
bne	$t0	$t1	Lab1
#	logical judgement	bne	    
lw	$t0	100($t9)	    
li	$t1	1	    
addu	$t2	$t0	$t1
sw	$t2	8($fp)	    
#	addu	    	    
lw	$t0	8($fp)	    
sw	$t0	100($t9)	    
#	assignment sentence	    	    
li	$t0	1	    
#	get the return value immediate number	    	    
sw	$t0	-8($fp)	    
#	save the value in the running stack	    	    
lw	$t8	-12($fp)	    
lw	$ra	-4($fp)	    
jr	$ra	    	    
#	jump back	    	    
j	    	    	Lab2
#	jump	    	    
Lab1	:	    	    
lw	$t0	0($fp)	    
li	$t1	2	    
bne	$t0	$t1	Lab3
#	logical judgement	bne	    
lw	$t0	100($t9)	    
li	$t1	1	    
addu	$t2	$t0	$t1
sw	$t2	12($fp)	    
#	addu	    	    
lw	$t0	12($fp)	    
sw	$t0	100($t9)	    
#	assignment sentence	    	    
li	$t0	1	    
#	get the return value immediate number	    	    
sw	$t0	-8($fp)	    
#	save the value in the running stack	    	    
lw	$t8	-12($fp)	    
lw	$ra	-4($fp)	    
jr	$ra	    	    
#	jump back	    	    
Lab3	:	    	    
Lab2	:	    	    
lw	$t0	100($t9)	    
li	$t1	1	    
addu	$t2	$t0	$t1
sw	$t2	16($fp)	    
#	addu	    	    
lw	$t0	16($fp)	    
sw	$t0	100($t9)	    
#	assignment sentence	    	    
lw	$t0	0($fp)	    
li	$t1	1	    
sub	$t2	$t0	$t1
sw	$t2	20($fp)	    
#	subtract	    	    
lw	$t0	20($fp)	    
sw	$t0	0($sp)	    
#	value parameter	    	    
li	$t8	64	    
jal	    	    	fib
lw	$v0	-8($fp)	    
subi	$fp	$fp	64
#function fib is 64	     	    	    
sw	$v0	24($fp)	    
#	call function	with return value	    
lw	$t0	0($fp)	    
li	$t1	2	    
sub	$t2	$t0	$t1
sw	$t2	28($fp)	    
#	subtract	    	    
lw	$t0	28($fp)	    
sw	$t0	0($sp)	    
#	value parameter	    	    
li	$t8	64	    
jal	    	    	fib
lw	$v0	-8($fp)	    
subi	$fp	$fp	64
#function fib is 64	     	    	    
sw	$v0	32($fp)	    
#	call function	with return value	    
lw	$t0	24($fp)	    
lw	$t1	32($fp)	    
addu	$t2	$t0	$t1
sw	$t2	36($fp)	    
#	addu	    	    
lw	$t0	36($fp)	    
#	get the return value	    	    
sw	$t0	-8($fp)	    
#	save the value in the running stack	    	    
lw	$t8	-12($fp)	    
lw	$ra	-4($fp)	    
jr	$ra	    	    
#	jump back	    	    
lw	$ra	-4($fp)	    
jr	$ra	    	    
#	jump back at the end of the function definition	    	    
hanoi	:	    	    
addu	$fp	$fp	$t8
sw	$t8	-12($fp)	    
sw	$ra	-4($fp)	    
#	hanoi function zone	    	    
lw	$a0	0($sp)	    
sw	$a0	0($fp)	    
#	parameter manipulation	    	    
lw	$a1	-4($sp)	    
sw	$a1	4($fp)	    
#	parameter manipulation	    	    
lw	$a2	-8($sp)	    
sw	$a2	8($fp)	    
#	parameter manipulation	    	    
lw	$a3	-12($sp)	    
sw	$a3	12($fp)	    
#	parameter manipulation	    	    
lw	$t0	0($fp)	    
li	$t1	1	    
bne	$t0	$t1	Lab4
#	logical judgement	bne	    
lw	$a0	4($fp)	    
li	$v0	11	    
syscall	    	    	    
#	print sentence type 3	    	    
li	$v0	4	    
la	$a0	str0	    
syscall	    	    	    
#	print sentence type 2	    	    
lw	$a0	12($fp)	    
li	$v0	11	    
syscall	    	    	    
#	print sentence type 3	    	    
li	$v0	4	    
la	$a0	str1	    
syscall	    	    	    
#	print sentence type 2	    	    
j	    	    	Lab5
#	jump	    	    
Lab4	:	    	    
lw	$t0	0($fp)	    
li	$t1	1	    
sub	$t2	$t0	$t1
sw	$t2	16($fp)	    
#	subtract	    	    
lw	$t0	16($fp)	    
sw	$t0	0($sp)	    
#	value parameter	    	    
lw	$t0	4($fp)	    
sw	$t0	-4($sp)	    
#	value parameter	    	    
lw	$t0	12($fp)	    
sw	$t0	-8($sp)	    
#	value parameter	    	    
lw	$t0	8($fp)	    
sw	$t0	-12($sp)	    
#	value parameter	    	    
li	$t8	52	    
jal	    	    	hanoi
subi	$fp	$fp	52
#function hanoi is 52	     	    	    
#	call function	without return value	    
lw	$a0	4($fp)	    
li	$v0	11	    
syscall	    	    	    
#	print sentence type 3	    	    
li	$v0	4	    
la	$a0	str2	    
syscall	    	    	    
#	print sentence type 2	    	    
lw	$a0	12($fp)	    
li	$v0	11	    
syscall	    	    	    
#	print sentence type 3	    	    
li	$v0	4	    
la	$a0	str3	    
syscall	    	    	    
#	print sentence type 2	    	    
lw	$t0	0($fp)	    
li	$t1	1	    
sub	$t2	$t0	$t1
sw	$t2	20($fp)	    
#	subtract	    	    
lw	$t0	20($fp)	    
sw	$t0	0($sp)	    
#	value parameter	    	    
lw	$t0	8($fp)	    
sw	$t0	-4($sp)	    
#	value parameter	    	    
lw	$t0	4($fp)	    
sw	$t0	-8($sp)	    
#	value parameter	    	    
lw	$t0	12($fp)	    
sw	$t0	-12($sp)	    
#	value parameter	    	    
li	$t8	52	    
jal	    	    	hanoi
subi	$fp	$fp	52
#function hanoi is 52	     	    	    
#	call function	without return value	    
lw	$t0	96($t9)	    
li	$t1	1	    
addu	$t2	$t0	$t1
sw	$t2	24($fp)	    
#	addu	    	    
lw	$t0	24($fp)	    
sw	$t0	96($t9)	    
#	assignment sentence	    	    
lw	$t8	-12($fp)	    
lw	$ra	-4($fp)	    
jr	$ra	    	    
#	jump back	    	    
Lab5	:	    	    
lw	$ra	-4($fp)	    
jr	$ra	    	    
#	jump back at the end of the function definition	    	    
swap	:	    	    
addu	$fp	$fp	$t8
sw	$t8	-12($fp)	    
sw	$ra	-4($fp)	    
#	swap function zone	    	    
lw	$a0	0($sp)	    
sw	$a0	0($fp)	    
#	parameter manipulation	    	    
lw	$a1	-4($sp)	    
sw	$a1	4($fp)	    
#	parameter manipulation	    	    
#	find variable	temp	    
li	$t0	4	    
lw	$t1	0($fp)	    
addu	$t2	$t0	$t1
li	$t5	4	    
mul	$t2	$t2	$t5
addu	$t2	$t2	$t9
lw	$t3	($t2)	    
sw	$t3	12($fp)	    
#	assign array element value to a identifier	    	    
lw	$t0	12($fp)	    
sw	$t0	8($fp)	    
#	assignment sentence	    	    
li	$t0	4	    
lw	$t1	4($fp)	    
addu	$t2	$t0	$t1
li	$t5	4	    
mul	$t2	$t2	$t5
addu	$t2	$t2	$t9
lw	$t3	($t2)	    
sw	$t3	16($fp)	    
#	assign array element value to a identifier	    	    
li	$t0	4	    
lw	$t1	0($fp)	    
addu	$t2	$t0	$t1
li	$t3	4	    
mul	$t3	$t3	$t2
addu	$t3	$t3	$t9
lw	$t4	16($fp)	    
sw	$t4	($t3)	    
#	assign value to the array element	    	    
li	$t0	4	    
lw	$t1	4($fp)	    
addu	$t2	$t0	$t1
li	$t3	4	    
mul	$t3	$t3	$t2
addu	$t3	$t3	$t9
lw	$t4	8($fp)	    
sw	$t4	($t3)	    
#	assign value to the array element	    	    
lw	$t0	104($t9)	    
li	$t1	1	    
addu	$t2	$t0	$t1
sw	$t2	20($fp)	    
#	addu	    	    
lw	$t0	20($fp)	    
sw	$t0	104($t9)	    
#	assignment sentence	    	    
lw	$t8	-12($fp)	    
lw	$ra	-4($fp)	    
jr	$ra	    	    
#	jump back	    	    
lw	$ra	-4($fp)	    
jr	$ra	    	    
#	jump back at the end of the function definition	    	    
quicksort	:	    	    
addu	$fp	$fp	$t8
sw	$t8	-12($fp)	    
sw	$ra	-4($fp)	    
#	quicksort function zone	    	    
lw	$a0	0($sp)	    
sw	$a0	0($fp)	    
#	parameter manipulation	    	    
lw	$a1	-4($sp)	    
sw	$a1	4($fp)	    
#	parameter manipulation	    	    
#	find variable	i	    
#	find variable	last	    
lw	$t0	0($fp)	    
lw	$t1	4($fp)	    
bge	$t0	$t1	Lab6
#	logical judgement	bge	    
lw	$t0	0($fp)	    
sw	$t0	12($fp)	    
#	assignment sentence	    	    
lw	$t0	0($fp)	    
li	$t1	1	    
addu	$t2	$t0	$t1
sw	$t2	16($fp)	    
#	addu	    	    
lw	$t0	16($fp)	    
sw	$t0	8($fp)	    
#	assignment sentence	    	    
Lab7	:	    	    
lw	$t0	8($fp)	    
lw	$t1	4($fp)	    
bgt	$t0	$t1	Lab8
#	logical judgement	bgt	    
li	$t0	4	    
lw	$t1	8($fp)	    
addu	$t2	$t0	$t1
li	$t5	4	    
mul	$t2	$t2	$t5
addu	$t2	$t2	$t9
lw	$t3	($t2)	    
sw	$t3	20($fp)	    
#	assign array element value to a identifier	    	    
li	$t0	4	    
lw	$t1	0($fp)	    
addu	$t2	$t0	$t1
li	$t5	4	    
mul	$t2	$t2	$t5
addu	$t2	$t2	$t9
lw	$t3	($t2)	    
sw	$t3	24($fp)	    
#	assign array element value to a identifier	    	    
lw	$t0	20($fp)	    
lw	$t1	24($fp)	    
bge	$t0	$t1	Lab9
#	logical judgement	bge	    
lw	$t0	12($fp)	    
li	$t1	1	    
addu	$t2	$t0	$t1
sw	$t2	28($fp)	    
#	addu	    	    
lw	$t0	28($fp)	    
sw	$t0	12($fp)	    
#	assignment sentence	    	    
lw	$t0	12($fp)	    
sw	$t0	0($sp)	    
#	value parameter	    	    
lw	$t0	8($fp)	    
sw	$t0	-4($sp)	    
#	value parameter	    	    
li	$t8	72	    
jal	    	    	swap
subi	$fp	$fp	72
#function quicksort is 72	     	    	    
#	call function	without return value	    
Lab9	:	    	    
lw	$t0	8($fp)	    
li	$t1	1	    
addu	$t2	$t0	$t1
sw	$t2	32($fp)	    
#	addu	    	    
lw	$t0	32($fp)	    
sw	$t0	8($fp)	    
#	assignment sentence	    	    
j	    	    	Lab7
#	jump	    	    
Lab8	:	    	    
lw	$t0	12($fp)	    
sw	$t0	0($sp)	    
#	value parameter	    	    
lw	$t0	0($fp)	    
sw	$t0	-4($sp)	    
#	value parameter	    	    
li	$t8	72	    
jal	    	    	swap
subi	$fp	$fp	72
#function quicksort is 72	     	    	    
#	call function	without return value	    
lw	$t0	12($fp)	    
li	$t1	-1	    
addu	$t2	$t0	$t1
sw	$t2	36($fp)	    
#	addu	    	    
lw	$t0	0($fp)	    
sw	$t0	0($sp)	    
#	value parameter	    	    
lw	$t0	36($fp)	    
sw	$t0	-4($sp)	    
#	value parameter	    	    
li	$t8	72	    
jal	    	    	quicksort
subi	$fp	$fp	72
#function quicksort is 72	     	    	    
#	call function	without return value	    
lw	$t0	12($fp)	    
li	$t1	1	    
addu	$t2	$t0	$t1
sw	$t2	40($fp)	    
#	addu	    	    
lw	$t0	40($fp)	    
sw	$t0	0($sp)	    
#	value parameter	    	    
lw	$t0	4($fp)	    
sw	$t0	-4($sp)	    
#	value parameter	    	    
li	$t8	72	    
jal	    	    	quicksort
subi	$fp	$fp	72
#function quicksort is 72	     	    	    
#	call function	without return value	    
Lab6	:	    	    
lw	$t8	-12($fp)	    
lw	$ra	-4($fp)	    
jr	$ra	    	    
#	jump back	    	    
lw	$t0	108($t9)	    
li	$t1	1	    
addu	$t2	$t0	$t1
sw	$t2	44($fp)	    
#	addu	    	    
lw	$t0	44($fp)	    
sw	$t0	108($t9)	    
#	assignment sentence	    	    
lw	$ra	-4($fp)	    
jr	$ra	    	    
#	jump back at the end of the function definition	    	    
main	:	    	    
addi	$fp	$fp	12
la	$ra	end_program	    
sw	$ra	-4($fp)	    
#	main zone	    	    
#	find variable	i	    
li	$t0	0	    
sw	$t0	96($t9)	    
#	assignment sentence	    	    
li	$t0	0	    
sw	$t0	100($t9)	    
#	assignment sentence	    	    
li	$t0	0	    
sw	$t0	104($t9)	    
#	assignment sentence	    	    
li	$t0	0	    
sw	$t0	108($t9)	    
#	assignment sentence	    	    
li	$t0	0	    
sw	$t0	112($t9)	    
#	assignment sentence	    	    
li	$t0	4	    
li	$t1	0	    
addu	$t2	$t0	$t1
li	$t3	4	    
mul	$t3	$t3	$t2
addu	$t3	$t3	$t9
li	$t4	4	    
sw	$t4	($t3)	    
#	assign value to the array element	    	    
li	$t0	4	    
li	$t1	1	    
addu	$t2	$t0	$t1
li	$t3	4	    
mul	$t3	$t3	$t2
addu	$t3	$t3	$t9
li	$t4	2	    
sw	$t4	($t3)	    
#	assign value to the array element	    	    
li	$t0	4	    
li	$t1	2	    
addu	$t2	$t0	$t1
li	$t3	4	    
mul	$t3	$t3	$t2
addu	$t3	$t3	$t9
li	$t4	9	    
sw	$t4	($t3)	    
#	assign value to the array element	    	    
li	$t0	4	    
li	$t1	3	    
addu	$t2	$t0	$t1
li	$t3	4	    
mul	$t3	$t3	$t2
addu	$t3	$t3	$t9
li	$t4	1	    
sw	$t4	($t3)	    
#	assign value to the array element	    	    
li	$t0	4	    
li	$t1	4	    
addu	$t2	$t0	$t1
li	$t3	4	    
mul	$t3	$t3	$t2
addu	$t3	$t3	$t9
li	$t4	5	    
sw	$t4	($t3)	    
#	assign value to the array element	    	    
li	$t0	4	    
li	$t1	5	    
addu	$t2	$t0	$t1
li	$t3	4	    
mul	$t3	$t3	$t2
addu	$t3	$t3	$t9
li	$t4	6	    
sw	$t4	($t3)	    
#	assign value to the array element	    	    
li	$t0	4	    
li	$t1	6	    
addu	$t2	$t0	$t1
li	$t3	4	    
mul	$t3	$t3	$t2
addu	$t3	$t3	$t9
li	$t4	8	    
sw	$t4	($t3)	    
#	assign value to the array element	    	    
li	$t0	4	    
li	$t1	7	    
addu	$t2	$t0	$t1
li	$t3	4	    
mul	$t3	$t3	$t2
addu	$t3	$t3	$t9
li	$t4	7	    
sw	$t4	($t3)	    
#	assign value to the array element	    	    
li	$t0	4	    
li	$t1	8	    
addu	$t2	$t0	$t1
li	$t3	4	    
mul	$t3	$t3	$t2
addu	$t3	$t3	$t9
li	$t4	3	    
sw	$t4	($t3)	    
#	assign value to the array element	    	    
li	$v0	4	    
la	$a0	str4	    
syscall	    	    	    
#	print sentence type 2	    	    
li	$t0	0	    
sw	$t0	0($fp)	    
#	assignment sentence	    	    
Lab10	:	    	    
lw	$t0	0($fp)	    
li	$t1	8	    
bge	$t0	$t1	Lab11
#	logical judgement	bge	    
li	$t0	4	    
lw	$t1	0($fp)	    
addu	$t2	$t0	$t1
li	$t5	4	    
mul	$t2	$t2	$t5
addu	$t2	$t2	$t9
lw	$t3	($t2)	    
sw	$t3	4($fp)	    
#	assign array element value to a identifier	    	    
li	$v0	4	    
la	$a0	str5	    
syscall	    	    	    
lw	$a0	4($fp)	    
li	$v0	1	    
syscall	    	    	    
#	print sentence type 1	    	    
lw	$t0	0($fp)	    
li	$t1	1	    
addu	$t2	$t0	$t1
sw	$t2	8($fp)	    
#	addu	    	    
lw	$t0	8($fp)	    
sw	$t0	0($fp)	    
#	assignment sentence	    	    
j	    	    	Lab10
#	jump	    	    
Lab11	:	    	    
li	$t0	0	    
sw	$t0	0($sp)	    
#	value parameter	    	    
li	$t0	8	    
sw	$t0	-4($sp)	    
#	value parameter	    	    
li	$t8	72	    
jal	    	    	quicksort
subi	$fp	$fp	72
#function main is 72	     	    	    
#	call function	without return value	    
li	$v0	4	    
la	$a0	str6	    
syscall	    	    	    
#	print sentence type 2	    	    
li	$t0	0	    
sw	$t0	0($fp)	    
#	assignment sentence	    	    
Lab12	:	    	    
lw	$t0	0($fp)	    
li	$t1	8	    
bge	$t0	$t1	Lab13
#	logical judgement	bge	    
li	$t0	4	    
lw	$t1	0($fp)	    
addu	$t2	$t0	$t1
li	$t5	4	    
mul	$t2	$t2	$t5
addu	$t2	$t2	$t9
lw	$t3	($t2)	    
sw	$t3	12($fp)	    
#	assign array element value to a identifier	    	    
li	$v0	4	    
la	$a0	str7	    
syscall	    	    	    
lw	$a0	12($fp)	    
li	$v0	1	    
syscall	    	    	    
#	print sentence type 1	    	    
lw	$t0	0($fp)	    
li	$t1	1	    
addu	$t2	$t0	$t1
sw	$t2	16($fp)	    
#	addu	    	    
lw	$t0	16($fp)	    
li	$t1	-858993460	    
addu	$t2	$t0	$t1
sw	$t2	20($fp)	    
#	addu	    	    
lw	$t0	20($fp)	    
sw	$t0	0($fp)	    
#	assignment sentence	    	    
j	    	    	Lab12
#	jump	    	    
Lab13	:	    	    
li	$v0	4	    
la	$a0	str8	    
syscall	    	    	    
li	$a0	-858993460	    
li	$v0	1	    
syscall	    	    	    
#	print sentence type 1	    	    
li	$t0	3	    
sw	$t0	0($sp)	    
#	value parameter	    	    
li	$t0	97	    
sw	$t0	-4($sp)	    
#	value parameter	    	    
li	$t0	98	    
sw	$t0	-8($sp)	    
#	value parameter	    	    
li	$t0	99	    
sw	$t0	-12($sp)	    
#	value parameter	    	    
li	$t8	72	    
jal	    	    	hanoi
subi	$fp	$fp	72
#function main is 72	     	    	    
#	call function	without return value	    
li	$v0	4	    
la	$a0	str9	    
syscall	    	    	    
lw	$a0	96($t9)	    
li	$v0	1	    
syscall	    	    	    
#	print sentence type 1	    	    
li	$v0	4	    
la	$a0	str10	    
syscall	    	    	    
lw	$a0	100($t9)	    
li	$v0	1	    
syscall	    	    	    
#	print sentence type 1	    	    
li	$v0	4	    
la	$a0	str11	    
syscall	    	    	    
lw	$a0	104($t9)	    
li	$v0	1	    
syscall	    	    	    
#	print sentence type 1	    	    
li	$v0	4	    
la	$a0	str12	    
syscall	    	    	    
lw	$a0	108($t9)	    
li	$v0	1	    
syscall	    	    	    
#	print sentence type 1	    	    
li	$v0	4	    
la	$a0	str13	    
syscall	    	    	    
#	print sentence type 2	    	    
li	$t0	12	    
li	$t1	15	    
mul	$t2	$t0	$t1
sw	$t2	24($fp)	    
#	multiply	    	    
li	$t0	86	    
li	$t1	84	    
mul	$t2	$t0	$t1
sw	$t2	28($fp)	    
#	multiply	    	    
li	$t0	-87	    
lw	$t1	28($fp)	    
addu	$t2	$t0	$t1
sw	$t2	32($fp)	    
#	addu	    	    
lw	$t0	24($fp)	    
lw	$t1	32($fp)	    
mul	$t2	$t0	$t1
sw	$t2	36($fp)	    
#	multiply	    	    
li	$t0	4	    
li	$t1	3	    
addu	$t2	$t0	$t1
li	$t5	4	    
mul	$t2	$t2	$t5
addu	$t2	$t2	$t9
lw	$t3	($t2)	    
sw	$t3	40($fp)	    
#	assign array element value to a identifier	    	    
lw	$t0	36($fp)	    
lw	$t1	40($fp)	    
addu	$t2	$t0	$t1
sw	$t2	44($fp)	    
#	addu	    	    
lw	$t0	44($fp)	    
li	$t1	1	    
bne	$t0	$t1	Lab15
#	logical judgement	bne	    
li	$v0	4	    
la	$a0	str14	    
syscall	    	    	    
#	print sentence type 2	    	    
j	    	    	Lab14
#	jump	    	    
Lab15	:	    	    
lw	$t0	44($fp)	    
li	$t1	98	    
bne	$t0	$t1	Lab16
#	logical judgement	bne	    
li	$v0	4	    
la	$a0	str15	    
syscall	    	    	    
#	print sentence type 2	    	    
j	    	    	Lab14
#	jump	    	    
Lab16	:	    	    
lw	$t0	44($fp)	    
li	$t1	99	    
bne	$t0	$t1	Lab17
#	logical judgement	bne	    
li	$v0	4	    
la	$a0	str16	    
syscall	    	    	    
#	print sentence type 2	    	    
j	    	    	Lab14
#	jump	    	    
Lab17	:	    	    
lw	$t0	44($fp)	    
li	$t1	1284664	    
bne	$t0	$t1	Lab18
#	logical judgement	bne	    
li	$v0	4	    
la	$a0	str17	    
syscall	    	    	    
#	print sentence type 2	    	    
j	    	    	Lab14
#	jump	    	    
Lab18	:	    	    
li	$v0	4	    
la	$a0	str18	    
syscall	    	    	    
#	print sentence type 2	    	    
Lab14	:	    	    
li	$v0	4	    
la	$a0	str19	    
syscall	    	    	    
#	print sentence type 2	    	    
li	$t0	3	    
li	$t1	1	    
bne	$t0	$t1	Lab20
#	logical judgement	bne	    
li	$v0	4	    
la	$a0	str20	    
syscall	    	    	    
#	print sentence type 2	    	    
j	    	    	Lab19
#	jump	    	    
Lab20	:	    	    
Lab19	:	    	    
li	$v0	4	    
la	$a0	str21	    
syscall	    	    	    
#	print sentence type 2	    	    
lw	$t8	-12($fp)	    
lw	$ra	-4($fp)	    
jr	$ra	    	    
#	jump back	    	    
lw	$ra	-4($fp)	    
jr	$ra	    	    
#	jump back at the end of the function definition	    	    
end_program :
