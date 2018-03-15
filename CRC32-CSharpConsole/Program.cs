using System;
using System.Text;

namespace CRC32_CSharpConsole
{
    internal static class Program
    {
        private static void Main(string[] args)
        {
            while (true)
            {
                var str = Console.ReadLine();
                if (str == null)
                {
                    break;
                }
                var arrayOfBytes = Encoding.UTF8.GetBytes(str);
                Console.WriteLine(Crc32.Crc32.Get(arrayOfBytes).ToString(@"X"));
            }
        }
    }
}
