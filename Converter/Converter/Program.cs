using System;

namespace Converter
{
    class Program
    {
        static void Main(string[] args)
        {
            ConvertNum Test = new ConvertNum();

            string strnum = Console.ReadLine();



            Test.ConvertNumber(16, 2, strnum);



        }
    }
}
