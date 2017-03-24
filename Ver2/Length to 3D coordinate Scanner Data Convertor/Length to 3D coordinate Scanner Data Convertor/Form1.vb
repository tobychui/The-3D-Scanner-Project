Public Class Form1
    Dim data() As String
    Dim tempspliter() As String
    Dim x As Double
    Dim y As Double
    Dim z As Double
    Dim r As Double 'radius
    Dim p As Double 'angle from center

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        On Error Resume Next
        data = TextBox1.Text.Split(vbNewLine)
        Dim rawdata As String
        For Each rawdata In data
            tempspliter = rawdata.Split(" ")
            'Put the right value into the right place
            x = tempspliter(0)
            y = tempspliter(1)
            z = tempspliter(2)
            'Data Analysis and sorting
            z = z / 22 'Convert z from steps to cm
            r = 65 - x 'Radius from center of rotating platform to object edge
            p = y / 2048 * 360 ' Convert angle from step to degree
            x = r * Math.Cos(p)
            y = r * Math.Sin(p)
            TextBox2.AppendText(x & " " & y & " " & z & vbNewLine)
        Next
    End Sub
End Class
