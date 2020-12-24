.data 

original_list: .space 100 
sorted_list: .space 100

str0: .asciiz "Enter size of list (between 1 and 25): "
str1: .asciiz "Enter one list element: \n"
str2: .asciiz "Content of original list: "
str3: .asciiz "Enter a key to search for: "
str4: .asciiz "Content of sorted list: "
strYes: .asciiz "Key found!"
strNo: .asciiz "Key not found!"

.text 

#This is the main program.
#It first asks user to enter the size of a list.
#It then asks user to input the elements of the list, one at a time.
#It then calls printList to print out content of the list.
#It then calls inSort to perform insertion sort
#It then asks user to enter a search key and calls bSearch on the sorted list.
#It then prints out search result based on return value of bSearch
main: 
	addi $sp, $sp -8
	sw $ra, 0($sp)
	li $v0, 4 			#print "Enter size of list (between 1 and 25): "
	la $a0, str0 
	syscall 
	li $v0, 5	#read size of list from user
	syscall
	move $s0, $v0			#s0 holds the size
	move $t0, $0			#t0 holds zero, (counter)
	la $s1, original_list		#s1 holds the original list
loop_in:
	li $v0, 4 			#print "Enter one list element: \n"
	la $a0, str1 
	syscall 
	sll $t1, $t0, 2			#t1 = 4*counter
	add $t1, $t1, $s1		#t1 = address+counter, to move up the array
	li $v0, 5	#read elements from user
	syscall
	sw $v0, 0($t1)			#store input to t1 stack, 0=5,1=4,2=3,3=2,4=1
	addi $t0, $t0, 1		#t0 = 0+1 = 1
	bne $t0, $s0, loop_in		#counter != size, else jump back to loop_in, 1=5
	move $a0, $s1			#store s1 to a0, the original list, 0
	move $a1, $s0			#store s0 to a1, size 
	
	jal inSort	#Call inSort to perform insertion sort in original list
	
	sw $v0, 4($sp)			#return sorted list into stack
	li $v0, 4 
	la $a0, str2 			#print "Content of original list: "
	syscall 
	la $a0, original_list		#pass two arguments, original list and size
	move $a1, $s0
	jal printList	#Print original list
	li $v0, 4 
	la $a0, str4 			#print "Content of sorted list: "
	syscall 
	lw $a0, 4($sp)			
	jal printList	#Print sorted list
	
	li $v0, 4 
	la $a0, str3 
	syscall 
	li $v0, 5	#read search key from user
	syscall
	move $a3, $v0
	lw $a0, 4($sp)
	jal bSearch	#call bSearch to perform binary search
	
	beq $v0, $0, notFound
	li $v0, 4 
	la $a0, strYes 
	syscall 
	j end
	
notFound:
	li $v0, 4 
	la $a0, strNo 
	syscall 
end:
	lw $ra, 0($sp)
	addi $sp, $sp 8
	li $v0, 10 
	syscall
	
	
#printList takes in a list and its size as arguments. 
#It prints all the elements in one line.
printList:
	#Your implementation of printList here	
   	
	#copy arguement to temp
	move $t0, $a0		#array
	move $t1, $a1		#size (dont need)
	li $t2, 0		#counter = 0
	
	
printLoop:	
	beq $t2, $t1, printEnd	#check counter == size   
	li $v0, 1		#prints list
	lw $a0, 0($t0)
	syscall
	
	li $v0, 11		#prints out space
	li $a0, 32	
	syscall
	
	addi $t0, $t0, 4	#increment array
	addi $t2, $t2, 1	#increment counter
	j printLoop
	
printEnd:
	li $v0, 11		#prints out newline
	li $a0, '\n'	
	syscall 
                
	jr $ra
	
	
#inSort takes in a list and it size as arguments. 
#It performs INSERTION sort in ascending order and returns a new sorted list
#You may use the pre-defined sorted_list to store the result
inSort:
	#Your implementation of inSort here
	la $t0, sorted_list
	lw $t1, 0($a0)
	sw $t1, 0($t0)
	
	addi $t2, $0, 1		# index i = 1
inSortFor:
	bge $t2, $s0, inSortEnd	# i < n
	
	sll $t3, $t2, 2		# t3 = bits to move in array, i multiply by 4
	add $t4, $a0, $t3	# t4 = address of o_arr+t3, old_arr+i 
	lw $t5, 0($t4)		# t5 = o_arr[i], key = o_arr[i]
	add $t6, $t2, -1	# j = i - 1 

inSortWhile:
	blt $t6, $0, last_step1	# j>=0
	sll $t3, $t6, 2
	add $t9, $t0, $t3
	lw $t7, 0($t9)		# t7 = n_arr[j]
	ble $t7, $t5, last_step2# arr[j] > key
	
	add $t8, $t6, 1		# j + 1
	sll $t3, $t8, 2		# multiply 4
	add $t4, $a0, $t3	# t4 = address of n_arr+j+1
	lw $t7, 0($t9)		# t7 = ,n_arr[j+1] = n_arr[j]
	sw $t7, 4($t9)		# n_arr[j] = t9
	add $t6, $t6, -1	# j = j - 1
	j inSortWhile
	
last_step1:
	sw $t5, 0($t9)
	add $t2, $t2, 1
	j inSortFor

last_step2:
	sw $t5, 4($t9)
	add $t2, $t2, 1
	j inSortFor
inSortEnd:
	la $v0, 0($t0)
	jr $ra
	
	
#bSearch takes in a list, its size, and a search key as arguments.
#It performs binary search RECURSIVELY to look for the search key.
#It will return a 1 if the key is found, or a 0 otherwise.
#Note: you MUST NOT use iterative approach in this function.
bSearch:
	sw $ra, 0($sp)			#store address

	beq 	$a1, $0, fail	
	
	srl	$t0, $a1, 1	# divde by 2
	sll	$t1, $t0, 2	# multiply by 4 	
	add	$t2, $t1, $a0	
	lw	$t3, 0($t2)	# mid 

	beq	$t3, $a3, found

	add	$a1, $t0, $0
	blt	$a3, $t3, bSearch
	
	addi	$t1, $t1, 4		
	add	$a0, $a0, $t1	# mid+1	
	addi $sp, $sp, -4
	jal 	bSearch
	lw $ra, 4($sp)
	addi $sp, $sp, 4		#push stack frame
	j 	endSearch
#found:
#	addi $v0, $0, 1
#	jr $ra
	
fail:
	
	addi $v0, $0, 0
	jr $ra

	
	
	