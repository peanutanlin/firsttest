objs=link.o
cfile=link.c

myapp:$(objs)
	gcc -o myapp $(objs) -g -w


$(objs):$(cfile)
	gcc -c $(cfile)
	
RM=del

clean:
	-$(RM) myapp.exe $(objs)