<4 x Int> A = <2, 5> ++ <3, 5>
[7 x Int] x = [1, 2, 3...]
[3 x Int] r = [1] ++ [2,4]

Float a = a ** 2

Int a = static_cast<float> 1.f
auto pl = dynamic_cast<Player> obj

String hello = "Hello " ++ "World!"

Vector<int> a = {1, 2, 4}
a.push(12)

onClick (lambda[a](Int x, Int y) -> Int

	auto r = a.pop()
	putStr x+y+r
	return x+y+r

end)

for (auto i : a)
...
end

for (Int a : range(0..10))
...
end

import system
import glfw
import openal
import opengl

enum Align = Left, Right, Center
typeclass Num = Int, Float, Double
alias String = [Char]

class MyList <Int size>
private:
	[Size x Int] data
	Int cursor = 0

public:

	def begin() -> ptr<Int> :: inline
		addr (data[0])

	def end() -> ptr<Int> :: inline
		addr (data[size-1])

	def next() -> ptr<Int> :: inline
		addr (data[++cursor])

	def prev() -> ptr<Int> :: inline
		addr (data[--cursor])

	def get() -> Int :: inline
		data[cursor]

end

alias Vec4f = <4 x Float> :: x <-> r, y <-> g, z <-> b, w <-> a
Vec4f color = <0,0,0,0>
color.a = 1;

const Mat4f.zero = [<0.f, ...>, ...]
const Mat4f.indent =
[
	<1.f, 0.f, 0.f ,0.f>,
	<0.f, 1.f, 0.f ,0.f>,
	<0.f, 0.f, 1.f ,0.f>,
	<0.f, 0.f, 0.f ,1.f>
]

def print (...)

end

def sum (const Num a, b) -> auto
	a+b

// Возведение в степень
def binary ** (<Num> a, <Num> a, b) -> auto :: inline
	fpow (a, b)
end

// Перемножение 2х чисел
def binary * (const Mat4f m1, m2) -> Mat4f :: inline

	Mat4f res

	for (Int i in [0..3]) :: unroll (all)

		Vec4f ci = m1[i][0]*m2[0];

		for (Int i in [0..3]) :: unroll (all)
			ci += m[i][j]*m2[j]

		res[i] = ci

	end

	return res

end

def updateMatrices()

	Mat4f mr = math::rotateMat    (Mat4f.indent, rotation, <0.f, 0.f, 1.f>)
	Mat4f mt = math::translateMat (Mat4f.indent, <position, 0.f>)
	Mat4f ms = math::scaleMat     (Mat4f.indent, <scale   , 1.f>)

	modelMatrix = mt*mr*ms;
	MVPMatrix   = camera.MVPMatrix*modelMatrix

end

[unique_ptr<Object>] objects
objects ++= object
objects.erase object.get()

[String <- unique_ptr<Object>] objects :: Hash
