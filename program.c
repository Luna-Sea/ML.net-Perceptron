using static System.Console;
class Perceptron
    {
    private double[] weights;
    private double bias;
    private double learningRate;
    public Perceptron(int FeatrueNum, double learningRate)
        {
        Random random = new Random();
        weights = new double[FeatrueNum];        
        for (int i = 0; i < FeatrueNum; i++)
            {
            weights[i] = random.NextDouble() * 2 - 1; // 在 -1 到 1 之间随机初始化权重w
            }
        bias = random.NextDouble() * 2 - 1;     //设置b值
        this.learningRate = learningRate;       //设置学习率
        }

    public int Predict(int[] inputs)
        {
        if (inputs.Length != weights.Length)
            {
            throw new ArgumentException("输入的维度与权重维度不匹配");
            }
        double sum = 0;
        for (int i = 0; i < inputs.Length; i++)
            {
            sum += inputs[i] * weights[i];
            }
        sum += bias;
        return (sum > 0) ? 1 : -1; // 使用阈值函数作为激活函数
        }

    public void Train(int[] inputs, int target)
        {
        int prediction = Predict(inputs);//初次分类结果
        int error = target - prediction; //判断分类是否错误

        for (int i = 0; i < weights.Length; i++)
            {
            weights[i] += learningRate * error * inputs[i];
            //下降梯度，learningRate * error就是梯度，inputs[i]是特征值影响（可选）
            }
        bias += learningRate * error;
        }
    public void output()
        {
        Console.WriteLine($"超平面方程为：");
        for (int i = 0;i < weights.Length;i++)
            {
            Write($"+ {weights[i]:F4} * x{i} ");
            }
        }
    }
class Program
    {
    static void Main()
        {
        int[][] trainingData = {
            new int[] {0, 0},
            new int[] {0, 1},
            new int[] {1, 0},
            new int[] {1, 1}
        };
        int[] labels = { -1, -1, -1, 1 };
        Perceptron perceptron = new Perceptron(FeatrueNum: 2, learningRate: 0.1);
        for (int epoch = 0; epoch < 100; epoch++)
            {
            for (int i = 0; i < trainingData.Length; i++)
                {
                perceptron.Train(trainingData[i], labels[i]);
                }
            }
        // 测试感知机
        Console.WriteLine("训练完成，开始预测：");
        Console.WriteLine("0 AND 0 = " + perceptron.Predict(new int[] { 0, 0 }));
        Console.WriteLine("0 AND 1 = " + perceptron.Predict(new int[] { 0, 1 }));
        Console.WriteLine("1 AND 0 = " + perceptron.Predict(new int[] { 1, 0 }));
        Console.WriteLine("1 AND 1 = " + perceptron.Predict(new int[] { 1, 1 }));
        perceptron.output();

        }
    }
