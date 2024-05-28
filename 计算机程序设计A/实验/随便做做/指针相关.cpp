class Program
    {
        static void Main(string[] args)
        {
            int num = 2019;
            while (true)
            {
                if (num%2019==0&&IsCheck(num))
                {
                    break;
                }
                num += 2019;
            }
            Console.WriteLine(num);
        }
        private static bool IsCheck(int num)
        {
        	//将字符转换成字符数组
            char[] cs = num.ToString().ToCharArray();
            foreach (var item in cs)
            {
                if ((int)item%2==0)
                {
                    return false;
                }
            }
            return true;
        }
    }

