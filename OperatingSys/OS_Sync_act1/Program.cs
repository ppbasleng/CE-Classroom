using System;
using System.Diagnostics;
using System.Threading;

namespace OS_Sync_act1
{
    class Program
    {
        private static string x = "";
        private static int exitflag = 0;
        private static int updateflag = 0;
        private static object _Lock = new object();
        static void ThReadx(object i)
        {

            while (exitflag == 0)
            {
                lock (_Lock)
                {
                    Monitor.Wait(_Lock);
                    if (x != "exit")
                    {   
                        
                        if(updateflag==1){
                            Console.WriteLine("***Thread {0} : x = {1}***", i, x);
                            updateflag = 0;
                        }
                        
                    }
                    
                }


            }
            Console.WriteLine("---Thread {0} exit***", i);
        }

        static void ThWritex()
        {
            string xx;
            while (exitflag == 0)
            {
                lock (_Lock)
                {
                    Monitor.PulseAll(_Lock);
                    Console.Write("input: ");
                    xx = Console.ReadLine();

                    if (xx == "exit")
                    {
                        exitflag = 1;
                    }else{
                        updateflag = 1;
                    }

                    x = xx;
                    
                }
            }
        }



        static void Main(string[] args)
        {

            Thread A = new Thread(ThWritex);
            Thread B = new Thread(ThReadx);
            Thread C = new Thread(ThReadx);
            Thread D = new Thread(ThReadx);

            A.Start();
            B.Start(1);
            C.Start(2);
            D.Start(3);

        }
    }
}
