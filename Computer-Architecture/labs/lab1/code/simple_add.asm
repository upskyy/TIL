.data
	msg: .asciiz "Result is "
.text
	li $t0, 16
	addi $t0, $t0, 4
	
	li $v0, 4
	la $a0, msg
	syscall
	
	li $v0, 1
	move $a0, $t0
	syscall
	
	li $v0, 10
	syscall