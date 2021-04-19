import math
import copy

def equal(a, b, e=1E-10):
    if -e < a - b < e: return True
    else: return False

class coord_systems:
	Cartesian = 0
	Polar = 1

class cartesian_coord:
	def __init__(self, x, y):
		self.x = x
		self.y = y

class polar_coord:
	def __init__(self, r, phi):
		self.r = r
		self.phi = phi

class Point:
	def __init__(self, a1 = 0, a2 = 0, coord_system = coord_systems.Cartesian):
		if type(a1) == str:
			self.a1, self.a2 = map(float, a1[1:-1].split(","))
			self.coord_system = coord_systems.Cartesian
		if (type(a1) == int) or (type(a1) == float):
			self.a1, self.a2 = a1, a2
			self.coord_system = coord_system

	def __eq__(p1, p2):
		return (abs(p1.a1 - p2.a1) <= 10**-10) and\
			   (abs(p1.a2 - p2.a2) <= 10**-10)

	def __ne__(p1, p2):
		return not (p1 == p2)

	def __repr__(self):
		return "("+str(self.a1)+","+str(self.a2)+")"

	def __str__(self):
		return repr(self)

	def __add__(p1, p2):
		if (p1.coord_system == coord_systems.Cartesian) and (p2.coord_system == coord_systems.Cartesian):
			return Point(p1.a1 + p2.a1, p1.a2 + p2.a2, coord_systems.Cartesian)

	def __sub__(p1, p2):
		if (p1.coord_system == coord_systems.Cartesian) and (p2.coord_system == coord_systems.Cartesian):
			return Point(p1.a1 - p2.a1, p1.a2 - p2.a2, coord_systems.Cartesian)

	def __mul__(p, float_variable):
		if p.coord_system == coord_systems.Cartesian:
			return Point(p.a1 * float_variable, p.a2 * float_variable, coord_systems.Cartesian)

	def to_cartesian(self, r, phi):
		return cartesian_coord(
			r * math.cos(phi), 
			r * math.sin(phi)
		)

	def to_polar(self, x, y):
		return polar_coord(
			math.hypot(x, y),
			math.atan2(y, x)
		)

	def get_x(self):
		return self.a1 if self.coord_system == coord_systems.Cartesian else self.to_cartesian(self.a1, self.a2).x

	def get_y(self):
		return self.a2 if self.coord_system == coord_systems.Cartesian else self.to_cartesian(self.a1, self.a2).y

	def get_r(self):
		return self.a1 if self.coord_system == coord_systems.Polar else self.to_polar(self.a1, self.a2).r

	def get_phi(self):
		return self.a2 if self.coord_system == coord_systems.Polar else self.to_polar(self.a1, self.a2).phi

	def set_x(self, x):
		if (self.coord_system == coord_systems.Cartesian):
			self.a1 = x
		else:
			coord = self.to_polar(x, self.to_cartesian(self.a1, self.a2).y)
			self.a1 = coord.r
			self.a2 = coord.phi

	def set_y(self, y):
		if (self.coord_system == coord_systems.Cartesian):
			self.a2 = y
		else:
			coord = self.to_polar(self.to_cartesian(self.a1, self.a2).x, y)
			self.a1 = coord.r
			self.a2 = coord.phi

	def set_r(self, r):
		if (self.coord_system == coord_systems.Polar):
			self.a1 = r
		else:
			coord = self.to_cartesian(r, self.to_polar(self.a1, self.a2).phi)
			self.a1 = coord.x;
			self.a2 = coord.y;

	def set_phi(self, phi):
		if (self.coord_system == coord_systems.Polar):
			self.a2 = phi;
		else:
			coord = self.to_cartesian(self.to_polar(self.a1, self.a2).r, phi)
			self.a1 = coord.x
			self.a2 = coord.y

class Vector:
	def __init__(self, begin = None, end = None):
		if (begin is None) and (end is None):
			self.begin = Point(0, 0)
			self.end = Point(1, 0)
			return
		if end is None:
			self.begin = Point(0, 0)
			self.end = begin
			return
		self.begin = begin
		self.end = end

	def __eq__(v1, v2):
		if v1.length() == v2.length():
			cosine = (v1*v2)/(v1.length()*v2.length())
			if cosine - 1 < pow(10, -10):
				return True
		return False

	def __neg__(self):
		return Vector(self.end, self.begin)

	def __add__(v1, v2):
		return Vector(v1.begin + v2.begin, v1.end + v2.end)

	def __sub__(v1, v2):
		return Vector(v1.begin - v2.begin, v1.end - v2.end)

	def __mul__(v1, x):
		if (type(x) == int) or (type(x) == float):
			return Vector(v1.begin * x, v1.end * x)
		if (type(x) == Vector):
			p1 = v1.end-v1.begin
			p2 = x.end-x.begin
			return p1.get_x()*p2.get_x() + p1.get_y()*p2.get_y()

	def length(self):
		p = self.end-self.begin;
		return math.hypot(p.get_x(), p.get_y())


# ===================================================================================


a = Vector(Point(1, 2))
b = Vector(Point(-2, 0), Point(-1, 2))
if a == b and b == a: print('Equality test passed')
else: print('Equality test failed')
  
na  = Vector(Point(-1, -2))
ox  = Vector(Point( 1,  0))
nox = Vector(Point(-1,  0))
oy  = Vector(Point( 0,  1))
noy = Vector(Point( 0, -1))
if a == -na and na == -a and -ox == nox and -oy == noy: print('Invert test passed')
else: print('Invert test failed')
  
if ox + oy + oy == a and -ox == -a + oy + oy: print('Summation test passed')
else: print('Summation test failed')
  
if -ox + oy == oy - ox and -oy + ox == ox - oy: print('Subtraction test passed')
else: print('Subtraction test failed')
  
if (ox * 3 == ox + ox + ox and
    oy * 3 == oy + oy + oy and
    ox * (-3) == -ox - ox - ox and
    oy * (-3) == -oy - oy - oy): print('Multiplication by number test passed')
else: print('Multiplication by number test failed')
  
if (equal(ox.length(), 1) and
    equal(oy.length(), 1) and
    equal((ox * 3 + oy * 4).length(), 5)): print('Length test passed')
else: print('Length test failed')
  
if (equal(ox*ox, ox.length()**2) and
    equal(oy*oy, oy.length()**2) and
    equal((ox*3 + oy*4)*(ox*3 + oy*4), (ox*3 + oy*4).length()**2)): print('Multiplication by Vector test passed')
else: print('Multiplication by Vector test failed')