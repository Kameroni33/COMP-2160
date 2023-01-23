all: excercise sign squash output

excercise: excercise1.c
	clang -Wall excercise1.c -o excercise

sign: sign.c
	clang -Wall sign.c -o sign

squash: squash.c
	clang -Wall squash.c -o squash

output: sign squash
	./sign <mywords.txt | sort | ./squash >output1.txt
	./sign <words.txt | sort | ./squash >output2.txt
	./sign </usr/share/dict/words | sort | ./squash >output3.txt

clean:
	rm excercise sign squash output1.txt output2.txt output3.txt

