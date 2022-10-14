#include <math.h>
#include <stdio.h>
int simplify(int num, int dom) {
  int max = num > dom ? num : dom;
  for (int i = 2; i <= max; i++) {
      if(num%i==0 && dom%i==0){
          return simplify(num / i, dom / i);
      }
  }
  printf("%d / %d", num, dom);
  return 0;
}
int main(void) {
  //Q1
  /*
  int x;
  printf("enter value for x: ");
  scanf("%d", &x);
  long ans;
  ans += 3*(pow((double) x, (double) 5));
  ans += 2*(pow((double) x, (double) 4));
  ans -= 5*(pow((double) x, (double) 3));
  ans -= (pow((double) x, (double) 2));
  ans += 7*x;
  ans -= 6;
  printf("%ld", ans);
*/

  //Q2
  /*
  int num1, dom1, num2, dom2;
  printf("enter two fractions seperated by a '+' (5/6+3/4): ");
  scanf("%d %*c %d %*c %d %*c %d", &num1, &dom1, &num2, &dom2);
  printf("%d %d %d %d\n", num1, dom1, num2, dom2);
  int newNum, newDom;
  newNum = num1 * dom2 + num2 * dom1;
  newDom = dom1 * dom2;
  simplify(newNum, newDom);
  */
  //Q3
  char a, b, c;
  printf("enter a 3 digit number: ");
  scanf("%c%c%c", &a, &b, &c);
  printf("the reversal is: %c%c%c", c, b, a);
}

