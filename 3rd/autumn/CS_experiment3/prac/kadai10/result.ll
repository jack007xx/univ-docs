@.str.w = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@.str.r = private unnamed_addr constant [3 x i8] c"%d\00", align 1
declare i32 @printf(i8*, ...)
declare i32 @__isoc99_scanf(i8 *, ...)

@x = common global i32 0, align 4

define i32 @main(){
	%1 = mul nsw i32 4, 5
	%2 = add nsw i32 2, %1
	%3 = sub nsw i32 %2, 7
	store i32 %3, i32* @x, align 4
	ret i32 0
}
