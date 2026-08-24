using System;
using System.IO;

namespace csclean
{
    internal class Class1
    {
        private static void Main(string[] args)
        {
            string[] filetypes = { "*.user", "*.suo", "*.scc", "*.ncb" };
            DirectoryInfo di = new DirectoryInfo(".");
            foreach (string ft in filetypes)
            {
                FileInfo[] fis = di.GetFiles(ft);
                foreach (FileInfo fi in fis)
                {
                    try
                    {
                        File.Delete(fi.Name);
                    }
                    catch (Exception e)
                    {
                        Console.WriteLine(e.Message);
                    }
                }
            }

            DirectoryInfo[] dis = new DirectoryInfo[]
            {
new DirectoryInfo("obj"),
new DirectoryInfo("bin"),
new DirectoryInfo("release"),
new DirectoryInfo("debug")
            };

            foreach (DirectoryInfo d in dis)
            {
                try
                {
                    d.Delete(true);
                }
                catch (DirectoryNotFoundException e)
                {
                    Console.WriteLine(e.Message);
                }
                catch (IOException e)
                {
                    Console.WriteLine(e.Message);
                }
                catch (System.UnauthorizedAccessException e)
                {
                    Console.WriteLine(e.Message);
                }
            }
        }
    }
}
