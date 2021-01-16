default:
	gcc date.c -o date
	gcc ls.c -o ls
	gcc cat.c -o cat
	gcc rm.c -o rm
	gcc mkdir.c -o mkdir 
	gcc Main.c
	./a.out
	rm a.out date ls cat rm mkdir