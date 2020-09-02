
	.data

cnt:	.word  16
numbers:	.word  15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0

	.text
main:	
	# t0: number counts (cnt)
	lw $t0, cnt($zero)

initsort:
    	subi $t0, $t0, 1            # Initialize bubblesort max count
    	addi $t3, $zero, 0        # Initialize i counter
    	
outerloop:
    	beq $t0, $t3, end
    	
    	addi $t2, $zero, 0        # Initialize data segment address counter
    	addi $t4, $zero, 0        # Initialize j counter
    	
    	j innerloop
    	
nexti:
    	addi $t3, $t3, 1          # Update i counter by 1
    	j outerloop               # Goto outerloop
    
innerloop:
    	beq $t0, $t4, nexti
    	
    	lw $t5, numbers($t2)        # Load from data segment address plus $t2 offset to $t5
	addi $t2, $t2, 4          # Add offset by 4 bytes
    	lw $t6, numbers($t2)        # Load from data segment address plus $t2 offset to $t6
    	
    	bgt $t5, $t6, swap        # If $t5 is greater than $t6 then swap
    	
nextj:
    	addi $t4, $t4, 1          # Update j counter by 1 
    	j innerloop               # Goto innerloop
    	
swap:
    	subi $t2, $t2, 4          # Subtract offset by 4 bytes
    	sw $t6, numbers($t2)        # Store from $t6 to data segment address plus $t2 offset
    	addi $t2, $t2, 4          # Add offset by 4 bytes 
    	sw $t5, numbers($t2)        # Store from $t5 to data segment address plus $t2 offset
    	j nextj                   # return to nextj
    	    	   	
end:
    	li $v0, 10                # System call to end the program
	syscall