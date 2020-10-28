using System;
using System.Runtime.InteropServices;
using AutomationServerTypeLibForDotNet;
public class CSharpAutomationClient
{
	public static void Main()
    {
        CMyMathClass obj = new CMyMathClass();
        IMyMath objIMyMath = (IMyMath) obj;

        int num1 = 75, num2 = 45, sum, sub;
        sum = objIMyMath.SumOfTwoIntegers(num1, num2);
        Console.WriteLine("Sum of " + num1 + "and " + num2 + "is " + sum);
        sub = objIMyMath.SubtractionOfTwoIntegers(num1, num2);
        Console.WriteLine("Subtraction of " + num1 + "and " + num2 + "is " + sub);
        Console.ReadLine();
    }
}
