.data
	array : .space 256
	title : .asciiz "*** Bubble Sort in odd and even sets ***"
	enter_length : .asciiz "\nEnter input length: "
	enter_value : .asciiz  "\nEnter input values: "
	output: .asciiz  "\nOutput:"
	odd : .asciiz  ">>Sorted Odd: " 
	even : .asciiz  ">>Sorted Even: "
	enter : .asciiz  "\n"
	space : .asciiz " "

.text
	main :
		li $v0, 4
		la $a0, title
		syscall  # print title
		
		la $a0, enter_length
		syscall  
		
		li $v0, 5	# get the number of length
		syscall
		move $t0, $v0
		
		li $v0, 4
		la $a0, enter_value
		syscall
		jal newline
		
		addi $t1, $0, 0        # Initialize inputloop counter
		addi $t2, $0, 0        # Initialize address counter
	
	inputloop :
		beq $t0, $t1, initset
		li $v0, 5             # get integer from the keyboard
		syscall
		sw $v0, array($t2)  
		addi $t1, $t1, 1
		addi $t2, $t2, 4	
		j inputloop
		
	initset :
		addi $t0, $t0, -1
		addi $t3, $0, 0      # Initialize i counter
		
	outerloop :
		beq $t0, $t3, printoutput   # if $t0 == $t3 , go to printoutput
		addi $t2, $0, 0      # Initialize address counter
		addi $t4, $t3, 0     # Initialize j counter  
		j innerloop
		
	i_plus :
		addi $t3, $t3 ,1  # update i++
		j outerloop
		
	innerloop :
		beq $t0, $t4, i_plus	# if $t0 == $t4 , go to i_plus
		
		lw $t5, array($t2)
		addi $t2, $t2, 4
		lw $t6, array($t2)
		bgt $t5, $t6, swap    # if $t5 > $t6 , go to swap
	
	j_plus :
		addi $t4, $t4, 1  # update j++
		j innerloop	   # go to innerloop
		
	swap :       
    		sw $t5, array($t2)        
    		addi $t2, $t2, -4          
    		sw $t6, array($t2)  
    		addi $t2, $t2, 4   
		j j_plus
	
	printoutput : 
		li $v0, 4
		la $a0, output     # print output String
		syscall
		addi $t0, $t0, 1   # Initialize display max count
		j printodd
		
	printset :
		addi $t1, $0, 0    # Initialize counter
		addi $t2, $0, 0    # Initialize address counter
		addi $s0, $0, 2    # save 2
		addi $s1, $0, 1    # save 1
		j newline
		jr $ra		# Jump to return address
		
	printodd :
		jal printset
		li $v0, 4
		la $a0, odd  # print odd String
		syscall
		
	checkodd :
		beq $t0, $t1, printeven
		lw $t5, array($t2)
		div $t5, $s0
		mfhi $s2   # remainder save
		beq $s2, $s1, printoddnum   # if odd , go to printoddnum
		addi $t2, $t2, 4	# update address counter
		addi $t1, $t1, 1	# update counter++
		j checkodd
		
	printoddnum :
		li $v0, 1
		lw $a0, array($t2)
		syscall
		li $v0, 4
		la $a0, space
		syscall
		addi $t2, $t2, 4	# update address counter
		addi $t1, $t1, 1	# update counter++
		j checkodd
		
	printeven :
		jal printset
		li $v0, 4
		la $a0, even
		syscall
	
	checkeven :
		beq $t0, $t1, end
		lw $t5, array($t2)
		div $t5, $s0
		mfhi $s2	# remainder save
		beq $s2, $0, printevennum	# if even , go to printevennum
		addi $t2, $t2, 4	# update address counter
		addi $t1, $t1, 1	# update counter++
		j checkeven
		
	printevennum :
		li $v0, 1
		lw $a0, array($t2)
		syscall
		li $v0, 4
		la $a0, space
		syscall
		addi $t2, $t2, 4	# update address counter
		addi $t1, $t1, 1	# update counter++
		j checkeven
		
	newline :
		li $v0, 4
		la $a0, enter
		syscall 
		jr $ra		# Jump to return address
	
	end :
		li $v0, 10
		syscall
		
		


