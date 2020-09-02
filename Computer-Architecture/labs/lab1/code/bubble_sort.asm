
.data
	array: .space 256         # Reserve in data segment up to a maximum of 64 integers
	msg1: .asciiz ".....Bubble Sort....."
	msg2: .asciiz "\nEnter Input Length: "
	msg3: .asciiz "\nEnter Input Values: "
	msg4: .asciiz "\nSorted Output Values:"
	newl: .asciiz "\n"
.text
     main:
     	# Display program title
	li $v0, 4                 # System call to print a string
	la $a0, msg1              # Load (msg1) address to the argument register
	syscall
	
	# prompt user to enter input length
	la $a0, msg2              # Load (msg2) address to the argument register
	syscall
	
	# Get the user's input
	li $v0, 5                 # System call to get integer from the keyboard
	syscall
	move $t0, $v0             # Move the user input to $t0

	li $v0, 4                 # System call to print a string
	la $a0, msg3              # Load (msg3) address to the argument register
	syscall
	jal newline               # Call newline
	
	addi $t1, $zero, 0        # Initialize scanloop counter
	addi $t2, $zero, 0        # Initialize data segment address counter
	    
    scanloop:
    	beq $t0, $t1, initsort    # If counter is equal to input length in $v0 then branch initsort
	li $v0, 5                 # System call to get integer from the keyboard
	syscall
	sw $v0, array($t2)
	
	addi $t2, $t2, 4          # Update data segment address counter
	addi $t1, $t1, 1          # Update loop counter
	
	j scanloop                # Goto scanloop
	
    initsort:
    	subi $t0, $t0, 1          # Initialize bubblesort max count
    	addi $t3, $zero, 0        # Initialize i counter
    	
    outerloop:
    	beq $t0, $t3, initdisp
    	
    	addi $t2, $zero, 0        # Initialize data segment address counter
    	addi $t4, $zero, 0        # Initialize j counter
    	
    	j innerloop
    	
    nexti:
    	addi $t3, $t3, 1          # Update i counter by 1
    	j outerloop               # Goto outerloop
    
    innerloop:
    	beq $t0, $t4, nexti
    	
    	lw $t5, array($t2)        # Load from data segment address plus $t2 offset to $t5
	addi $t2, $t2, 4          # Add offset by 4 bytes
    	lw $t6, array($t2)        # Load from data segment address plus $t2 offset to $t6
    	
    	bgt $t5, $t6, swap        # If $t5 is greater than $t6 then swap
    	
    nextj:
    	addi $t4, $t4, 1          # Update j counter by 1 
    	j innerloop               # Goto innerloop
    	
    swap:
    	subi $t2, $t2, 4          # Subtract offset by 4 bytes
    	sw $t6, array($t2)        # Store from $t6 to data segment address plus $t2 offset
    	addi $t2, $t2, 4          # Add offset by 4 bytes 
    	sw $t5, array($t2)        # Store from $t5 to data segment address plus $t2 offset
    	j nextj                   # return to nextj
    	
    initdisp:
    	addi $t0, $t0, 1          # Initialize display max count
    	addi $t1, $zero, 0        # Initialize display counter
    	addi $t2, $zero, 0        # Initialize data segment address counter
    	
    	li $v0, 4                 # System call to print a string
	la $a0, msg4              # Load (msg4) address to the argument register
	syscall
	jal newline               # Call newline
    	
    display:
    	beq $t0, $t1, end         # If counter is equal to max count in $t0 then branch end
    	
    	li $v0, 1                 # System call to print an integer
    	lw $a0, array($t2)        # Load from data segment address plus $t2 offset to $a0
	syscall
    	jal newline               # Call newline
    	
    	addi $t2, $t2, 4          # Update data segment address counter
	addi $t1, $t1, 1          # Update display counter
	
	j display                 # Goto display
    	
    newline:
    	li $v0, 4                 # System call to print a string
	la $a0, newl              # Load (newl) address to the argument register
	syscall
	jr $ra                    # Jump to return address
    	
    end:
    	li $v0, 10                # System call to end the program
	syscall
