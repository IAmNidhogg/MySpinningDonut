# My Spinning Donut

Status: Done

# 简介/Introduction

画一个简单的甜甜圈，然后让它旋转起来，再把它在终端上展示出来。

Draw a simple donut and make it spin. Then show it on the terminal.

参考文章

Reference article

https://www.a1k0n.net/2021/01/13/optimizing-donut.html

https://www.a1k0n.net/2011/07/20/donut-math.html

https://youtu.be/sW9npZVpiMI?si=SCTS3gHpac2LqNwQ

# 原理

## 旋转原理

首先介绍旋转的原理。我们以三维坐标系中，一个xz平面上的点绕y轴旋转为例，来详细介绍。

作出示意图如下图所示：

![image.png](My%20Spinning%20Donut%201baa5355d9308143bacbc917ff85183f/image.png)

设向量$A = (x, y, z)$的模为$|A|$，其与z轴正半轴的夹角为$\alpha$，那么我们可以分别将$x, y, z$表示为：

$$
\left\{\begin{matrix}x = |A|\cdot \sin \alpha \\ y = c (Constant) \\z = |A|\cdot \cos \alpha 
\end{matrix}\right.
$$

将向量$A$绕$y$轴旋转角度$\beta$，得到向量$A^{'} = (x^{'}, y^{'}, z^{'})$，其模为$|A^{'}|$，同样将其表示为：

$$
\left\{\begin{matrix}x^{'} = |A|\cdot \sin (\alpha + \beta) \\ y^{'} = c (Constant) \\z^{'} = |A|\cdot \cos (\alpha + \beta) 
\end{matrix}\right.
$$

利用和差角公式：

$$
\left\{\begin{matrix}
\sin(\alpha + \beta) = \sin\alpha \cdot\cos\beta+\cos\alpha\cdot\sin\beta\\ \cos(\alpha+\beta)=\cos\alpha\cdot\cos\beta-\sin\alpha\cdot\sin\beta

\end{matrix}\right.
$$

可以得到如下结果：

$$
\left\{\begin{matrix}x^{'} = |A|\sin \alpha\cos\beta+|A|\cos\alpha\sin\beta = x\cos\beta + z\sin\beta \\ z^{'} = |A|\cos\alpha\cos\beta-|A|\sin\alpha\sin\beta=z\cos\beta-x\sin\beta

\end{matrix}\right.
$$

我们将这个结果写成矩阵的形式：

$$
\begin{pmatrix}x^{'} \\y^{'} \\z^{'}\end{pmatrix} = \begin{pmatrix}\cos\beta  &0  &\sin\beta \\0  &1  &0 \\-\sin\beta  &0  &\cos\beta \end{pmatrix} \begin{pmatrix} x\\ y\\z
\end{pmatrix}
$$

由此我们得到了绕$y$轴旋转角度$\beta$的旋转矩阵，并将其命名为$M_{y}(\beta)$，同理我们还可以分别得到绕$x$轴和$z$轴旋转角度$\beta$的旋转矩阵：

$$
M_{x}(\beta)=\begin{pmatrix}1  &0  &0 \\0  &\cos\beta  &-\sin\beta \\0  &\sin\beta  &\cos\beta \end{pmatrix} 
$$

$$
M_{z}(\beta)=\begin{pmatrix}\cos\beta  &-\sin\beta  &0 \\\sin\beta  &\cos\beta  &0 \\0  &0  &1 \end{pmatrix} 
$$

最后，如果我们让任意向量$(x, y, z)$同时分别绕$x$轴、$y$轴和$z$轴旋转角度$A$、$\phi$和$B$，那么旋转后的向量坐标为：

$$
\begin{pmatrix} x^{'}\\ y^{'}\\z^{'}
\end{pmatrix}=M_{z}(B)\cdot M_{x}(A)\cdot M_{y}(\phi )\begin{pmatrix} x\\ y\\z
\end{pmatrix}
$$

需要注意的是，在做矩阵乘法时，坐标是用一维列向量的形式来表示的，旋转矩阵是左乘，所以这里的旋转顺序是，先绕$y$轴旋转角度$\phi$，再绕$x$轴旋转角度A，最后绕$z$轴旋转角度B。

## 画一个三维的甜甜圈

首先如下图所示在二维平面上画一个圆：

![image.png](My%20Spinning%20Donut%201baa5355d9308143bacbc917ff85183f/image%201.png)

我们用极坐标来表示圆上的点：

$$
\left\{\begin{matrix}x = R_{2}+R_{1}\cos\theta  \\y=R_{1}\sin\theta \\z=0\end{matrix}\right.
$$

接下来我们让这个圆绕y轴旋转一周，就能够得到一个完整的立体的甜甜圈上所有的点坐标。

[https://www.desmos.com/3d/zefktqwyu4](https://www.desmos.com/3d/zefktqwyu4)

根据之前的旋转原理，可以轻易由圆上的点坐标得到甜甜圈的点坐标。因为最终我们要让甜甜圈在三个坐标轴上都有旋转，这里我们能够直接表示出最终的所有点坐标：

$$
\begin{pmatrix} x^{'}\\ y^{'}\\z^{'}
\end{pmatrix}=M_{z}(B)\cdot M_{x}(A)\cdot M_{y}(\phi )\begin{pmatrix} R_{2}+R_{1}\cos\theta\\ R_{1}\sin\theta\\0
\end{pmatrix}
$$

将其具体计算出来就是：

## 投射到2D平面

因为我们最终需要将立体的甜甜圈展示在屏幕上，而屏幕本身显示的是一个“二维”的图像，因此我们在得到甜甜圈的坐标后还需要将它们投射到2D屏幕上。作出示意图如下图所示：

![image.png](My%20Spinning%20Donut%201baa5355d9308143bacbc917ff85183f/image%202.png)

可以看到，如果把人眼所在位置定位坐标原点，那么屏幕到眼睛的距离就是$z^{'}$，我们用参数$K_{1}$来表示。由正切$tan$相等有：

$$
\frac{y}{z}=\frac{y^{'}}{z^{'}},\frac{x}{z}=\frac{x^{'}}{z^{'}}
$$

所以屏幕上的点坐标为：

$$
(x^{'},y^{'},z^{'})=(\frac{xz^{'}}{z},\frac{yz^{'}}{z},z^{'})=(\frac{xK_{1}}{z},\frac{yK_{1}}{z},z^{'})
$$

然后我们再添加一个移动参数，便于我们调整甜甜圈的位置。该参数为$K_{2}$，用来更新物体到眼睛的距离$z$，即$z =z + K_2$，所以点坐标为：

$$
(x^{'},y^{'},z^{'})=(\frac{xK_{1}}{z+K_2},\frac{yK_{1}}{z+K_2},z^{'})
$$

## 绘制阴影

虽然我们已经将立体的甜甜圈点坐标都投射到2D屏幕上了，但此时我们还不能较为直观且美观地看到这个甜甜圈，因为我们还没有给甜甜圈加上阴影，让它真正“立体”起来。

物体明暗表现的基本原理可以概括为：物体表面法线和光线方向的点积，若点积大于零，则物体上该点是明亮的；若点积小于零，则物体上该点是阴暗的；点积越大越明亮，点积越小越阴暗。

这里为了方便，我们直接固定光源，也就是固定光线方向，并假设光源发出的都是平行光，即所有的光线方向都一致，我们设为$(0,1,-1)$。

接下来我们需要得到甜甜圈上每个点的法线方向。此时会议之前构造甜甜圈的过程，我们其实可以直接在以原点为中心的单位圆上先作出每个点的法线，它们是与画甜甜圈的初始圆圈上的法线方向一致的，然后将它们按照相同的方式旋转，就能够得到所有点的法线方向了！我们用$(N_x,N_y,N_z)$表示法线：

$$
\begin{pmatrix} N_x\\ N_y\\N_z
\end{pmatrix}=M_{z}(B)\cdot M_{x}(A)\cdot M_{y}(\phi )\begin{pmatrix} \cos\theta\\\sin\theta\\0
\end{pmatrix}
$$

最后得到点积$L$：

$$
L = (N_X,N_y,N_z)\cdot(0,1,-1)=N_y-N_z
$$

最后得到：

$$
L = \cos\theta\cos\phi\sin(B)+\cos\theta\sin\phi\cos(A)-\sin\theta\sin(A)+\cos(B)(\sin\theta\cos(A)+\cos\theta\sin\phi\sin(A))
$$

## 简化计算

不难发现，在绘制圆形时，我们需要在多层循环下多次计算$\sin$和$\cos$函数，这不是很高效，因此我们同样可以借助旋转矩阵来完成。不过这里借助的是二维的旋转矩阵：

$$
\begin{pmatrix} \cos^{'}\\\sin^{'}\end{pmatrix}=\begin{pmatrix}\cos\theta   &-\sin\theta  \\\sin\theta   &\cos\theta \end{pmatrix}\begin{pmatrix}\cos \\\sin \end{pmatrix}
$$

这样当我们选定步长$(\theta)$之后，就可以在旋转的过程中得到每一个角度的三角函数值，这样做最直观的好处就是只需要计算一次$\cos$和$\sin$的值，之后只需要做乘法即可。

## 精度修正

在简化计算部分，我们已经知道整个流程只需要计算一次三角函数值。但是在计算时我们会发现，我们得到的三角函数值并非完全“精准”，因为它们是无理数，所以我们自然会有近似，于是就会有新的问题。因为同一角度的三角函数必须满足：

$$
\cos^2 + \sin^2 = 1
$$

但是在多次旋转之后，我们得到的三角函数值将不能够满足以上条件。直观来说，随着旋转的进行，会出现如下图所示的情况：（将尺度放大）

![image.png](My%20Spinning%20Donut%201baa5355d9308143bacbc917ff85183f/image%203.png)

如图a所示，随着旋转，直观体现是向量模长会变短，如果只看点的话，就会出现图b所示的情况。因此我们需要在一定程度上修正这样的误差。

首先能够想到的最简单的修正即：

$$
\left\{\begin{matrix}\cos = \frac{\cos}{\sqrt{\cos^2 + \sin^2}}  \\\sin=\frac{\sin}{\sqrt{\cos^2+\sin^2}}
\end{matrix}\right.
$$

这样就能够确保满足平方的和保持为1。但是在本次项目中，我们不能够使用math库（根号运算）。因此再观察上面的修正方法，我们可以概括出，我们的目标其实是找到$\sqrt{\cos^2+\sin^2}$的倒数，即$\frac{1}{\sqrt{\cos^2+\sin^2}}$，因此我们采用牛顿法求根来解决这个问题。

首先令：

$$
f(x)=\frac{1}{x^2}-a
$$

因为$f(x)$是实值函数，并且可导，我们假设初始猜测$x_0 = 1$，则根据迭代公式：

$$
x_{n+1}=x_n-\frac{f(x_n)}{f^{'}(x_n)}
$$

可以求出：

$$
x_1=\frac{3-a}{2}
$$

因为在我们的情境中，初始值已经很接近1了，所以只需要进行一步修正即可，并且$a=\cos^2+\sin^2$，所以我们实际使用的修正项为：

$$
K_{correct} = \frac{3-\cos^2-\sin^2}{2}
$$

所以我们计算三角函数值的公式修正为：

$$
\begin{pmatrix} \cos^{'}\\\sin^{'}\end{pmatrix}=K_{corect}\begin{pmatrix}\cos\theta   &-\sin\theta  \\\sin\theta   &\cos\theta \end{pmatrix}\begin{pmatrix}\cos \\\sin \end{pmatrix}
$$

进一步做一些调整有：

$$
\begin{pmatrix} \cos^{'}\\\sin^{'}\end{pmatrix}=K_{correct}\cos\theta\begin{pmatrix}1   &-\tan\theta  \\\tan\theta   &1 \end{pmatrix}\begin{pmatrix}\cos \\\sin \end{pmatrix}
$$

然后再让：

$$
K_{correct} = \frac{3-\cos^2-\sin^2}{2}\cos
$$

这样就有：

$$
\begin{pmatrix} \cos^{'}\\\sin^{'}\end{pmatrix}=K_{correct}\begin{pmatrix}1   &-\tan\theta  \\\tan\theta   &1 \end{pmatrix}\begin{pmatrix}\cos \\\sin \end{pmatrix}
$$

这样旋转矩阵里只需要提前计算$\tan\theta$，还能够进一步减少产生的误差。

# 实现

接下来，我们就可以按照理论分析，将这一切写成代码，在屏幕上绘制出甜甜圈来了！


