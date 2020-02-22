using System;
using System.Collections.Generic;
using System.Text;

namespace Converter
{
    class ConvertNum
    {
        private int checkNumBase(int p1, string strnum) //проверяем, что все цифры меньше основания системы счисления: 1 - все ок, 0 - входные данные неверные
        {
            string str_base = "";

            if (p1 > 1 && p1 < 10)
                str_base = Convert.ToString(p1);
            else
                if (p1 > 9 && p1 < 16) ;
            {
                str_base = Convert.ToString((char)(p1 + 55));
            }


            for (int i = 0; i < strnum.Length; i++)
            {
                if (strnum[i] >= str_base[0])
                    return 0;
               
            }
            return 1;
        }

        public void ConvertNumber(int p1, int p2, string strnum) //основная функция, которой пользуется пользователь
        {
            strnum = ConvertBaseTo10(p1, strnum); //возвращает пустую строку если что-то было не так с данными

            if (strnum != "")
                strnum = Convert10ToBase(p2, strnum); 
            else
                strnum = "Некорректно введено число"; //сообщение чтобы отслеживать


            Console.WriteLine(strnum);

        }
        private string Convert10ToBase(int p2, string strnum)
        {
            int num1 = 0, flag = 0;
            string str1, str2="", str_res1 = "", str_res2 = "", str_buf, str_res;
            int num_res1 = 0;
            double num2 = 0, num_res2 = 0;


            for (int i = 0; i < strnum.Length && flag != 1; i++)
            {
                if (strnum[i] == ',')
                    flag = 1;
            }

            if (flag == 1)
            {
                string[] nums = strnum.Split(',');
                str1 = nums[0];
                str2 = nums[1];
                num1 = int.Parse(str1);
                num2 = double.Parse(str2);
            }
            else
                num1 = int.Parse(strnum);


            int flag_minus = 0;
            if (strnum[0] == '-')
            { 
                flag_minus = 1;
                num1 *= -1;
            }



            /* РАЗБИРАЕМСЯ С ЦЕЛОЙ ЧАСТЬЮ */
            while (num1 >= p2) 
            {
                num_res1 = num1 % p2;

                if (num_res1 >= 10 && num_res1 <= 15)
                {
                    num_res1 += 55;
                    str_buf = Convert.ToString((char)num_res1);
                }
                else
                { str_buf = Convert.ToString(num_res1); }

                str_res1 += str_buf;
                
                num1 = num1 / p2;
            }
            num_res1 = num1;

           
            str_buf = Convert.ToString(num_res1);
            str_res1 += str_buf;

            char[] s1 = str_res1.ToCharArray();
            Array.Reverse(s1);

            

            str_res1 = new string(s1);

            if (flag_minus == 1)
            {
                str_res1 = str_res1.Insert(0, "-");
            }
            /* РАЗБИРАЕМСЯ С ЦЕЛОЙ ЧАСТЬЮ */

            /* РАЗБИРАЕМСЯ С ДРОБНОЙ ЧАСТЬЮ */

            if (flag == 1)
            {
                str2 = "0," + str2;

                num2 = double.Parse(str2);



                for (int i = 0; i < 8; i++)
                {
                    num2 = num2 * p2;

                    if (Math.Truncate(num2) >= 10 && Math.Truncate(num2) <= 15)
                    {
                        num2 += 55;
                        str_buf = Convert.ToString((char)Math.Truncate(num2));
                    }
                    else
                    { str_buf = Convert.ToString(Math.Truncate(num2)); }

                    str_res2 = str_res2 + str_buf;

                    num2 -= Math.Truncate(num2);

                }

                str_res = str_res1 + "." + str_res2;
            }
            else
                str_res = str_res1;

            /* РАЗБИРАЕМСЯ С ДРОБНОЙ ЧАСТЬЮ */

            //Console.WriteLine(str_res);
            return str_res;

        }
        private string ConvertBaseTo10(int p1, string strnum)
        {

            int num = 0, mod, k = 0, flag_sym = 0, check_num = 0;

            double numres = 0;

            int i = 0, count = 0;

            if (strnum[0] == '-')
            {
                flag_sym = 1;
                strnum = strnum.Remove(0, 1);
            }


            strnum = strnum.Replace('.', ',');

            while (i < strnum.Length)
            {


                if (strnum[i] == ',')
                {
                    
                    count = strnum.Length - i - 1;
                    //strnum = strnum.Remove(i, 1);
                    
                    break;
                }
              
               

                i++;

            }

            k = -count;

            check_num = checkNumBase(p1, strnum);

            if (strnum[0] == '0' && strnum[1] != ',')
                check_num = 0;
            

            if (check_num == 1)
            {
                for (int j = strnum.Length - 1; j >= 0; j--)
                {
                    if (strnum[j] >= '0' && strnum[j] <= '9')
                    {
                        num = strnum[j] - '0';
                        numres += num * Math.Pow(p1, k);
                        k++;
                    }
                    else
                        if (strnum[j] >= 'A' && strnum[j] <= 'F')
                    {
                        num = strnum[j] - 55;
                        numres += num * Math.Pow(p1, k);
                        k++;
                    }



                }

                if (flag_sym == 1)
                    numres *= -1;

                string str_res = Convert.ToString(numres);
                //Console.WriteLine(str_res);
                return str_res;
            }
            else
                return "";
        }

        
    }
}
