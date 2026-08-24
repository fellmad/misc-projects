using System.IO;
using System.Windows;
using System.Windows.Controls;
public partial class Window1 : Window
{
    private string GetCleanFileName(string filename)
    {
        filename = filename.Replace("/", "_");
        filename = filename.Replace("\\", "_");
        filename = filename.Replace(" ", "");
        return filename;
    }

    public Window1()
    {
        PrintDialog printDialog = new PrintDialog();
        var result = printDialog.ShowDialog();
        if (true != result)
        {
            Close();
            return;
        }

        string printTicketXmlFileName = string.Format("{0}_printTicket.xml", printDialog.PrintQueue.FullName);
        printTicketXmlFileName = GetCleanFileName(printTicketXmlFileName);
        FileStream printTicketXmlFileStream = new FileStream(printTicketXmlFileName, FileMode.Create);
        var printTicket = printDialog.PrintTicket;
        printTicket.SaveTo(printTicketXmlFileStream);
        printTicketXmlFileStream.Close();
        System.Console.WriteLine(printTicketXmlFileName + " saved");

        string printCapabilitiesXmlFileName = string.Format("{0}_printCapabilities.xml", printDialog.PrintQueue.FullName);
        printCapabilitiesXmlFileName = GetCleanFileName(printCapabilitiesXmlFileName);
        FileStream printCapabilitiesXmlFileStream = new FileStream(printCapabilitiesXmlFileName, FileMode.Create);
        MemoryStream printCapabilitiesStream = printDialog.PrintQueue.GetPrintCapabilitiesAsXml();
        printCapabilitiesStream.WriteTo(printCapabilitiesXmlFileStream);
        printCapabilitiesXmlFileStream.Close();
        System.Console.WriteLine(printCapabilitiesXmlFileName + " saved");

        Close();
    }
}