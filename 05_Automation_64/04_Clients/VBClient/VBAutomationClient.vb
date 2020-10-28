Imports System.Windows.Forms
Imports AutomationServerTypeLibForDotNet

Public Class VBAutomationClient
    Inherits Form

    Public Sub New()

        Dim MyIDispatch As Object
        Dim MyRef As New CMyMathClass
        MyIDispatch = MyRef

        Dim Num1 = 75
        Dim Num2 = 55
        Dim Sum = MyIDispatch.SumOfTwoIntegers(Num1, Num2)
        Dim str = String.Format("Sum Of {0} and {1} is {2}", Num1, Num2, Sum)
        MsgBox(str)


        Dim ObjSub = MyIDispatch.SubtractionOfTwoIntegers(Num1, Num2)
        str = String.Format("Subtraction Of {0} and {1} is {2}", Num1, Num2, ObjSub)
        MsgBox(str)
        End
    End Sub

    <STAThread>
    Shared Sub Main()
        Application.EnableVisualStyles()
        Application.Run(New VBAutomationClient())
    End Sub

End Class
