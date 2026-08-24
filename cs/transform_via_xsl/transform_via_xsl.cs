// msbuild C:\cedar_svn_trig_sandbox\TNG\TNG\Driver\src\common\common.vcxproj /p:RunCodeAnalysis=true
// csc.exe this file

using System.IO;
using System.Xml;
using System.Xml.Xsl;

class Program {
  private const string sourceFile = @"C:\cedar_svn_trig_sandbox\TNG\TNG\Driver\src\common\Win7Debug\vc.nativecodeanalysis.all.xml";
  private const string outputFile = @"c:\temp\code_anal.html";

  // private const string stylesheet = @"c:\apps\vs2015\Team Tools\Static Analysis Tools\FxCop\Xml\CodeAnalysisReport.xsl";
  // private const string stylesheet = @"c:\apps\vs2015\Team Tools\Static Analysis Tools\FxCop\Xml\FxCopReport.xsl";
  private const string stylesheet = @"c:\apps\vs2015\Team Tools\Static Analysis Tools\FxCop\Xml\VSConsoleOutput.xsl";

  static void Main(string[] args) {
    // Enable XSLT debugging.
    XslCompiledTransform xslt = new XslCompiledTransform();

    // Compile the style sheet.
    xslt.Load(stylesheet);

    // Execute the XSLT transform.
    FileStream outputStream = new FileStream(outputFile, FileMode.Append);
    xslt.Transform(sourceFile, null, outputStream);
  }
}
