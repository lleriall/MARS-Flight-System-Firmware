%{
    MIT License
Copyright (c) 2023 Limitless Aeronautics
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
%}
%Test Data

_pathInitial = [5,9]
_pathFinal = [15,24]

%Check if final x or y is equal to initial x or y within the bounds of 10%
if(_pathInitial(0) >= _pathFinal(0) - (0.10 * _pathFinal(0)) && _pathInitial(0) <= _pathFinal(0) + (0.10 * _pathFinal(0))):
    %Current Angle does not change

end
if(_pathInitial(1) >= _pathFinal(1) - (0.10 * _pathFinal(0)) && _pathInitial(0) <= _pathFinal(0) + (0.10 * _pathFinal(0))):
    %Current Angle does not change

end

%else
%Map out y value to finish path triangle
%(initial X, final Y)
%Use data to finish path triangle
%(initial X, finaly Y)
%(initial X, initial Y)
%(final X, final Y)
mappedVector = [_pathInitial(0),_pathFinal(1)];

%Get distance from initial vector to final vector
dInitial_Final = sqrt(power(_pathFinal(0) - _pathInitial(0),2) + power(_pathFinal(1) - _pathInitial(1),2));
%Get distance from initial vector to mapped vector
dInitial_Mapped = sqrt(power(mappedVector(0) - _pathInitial(0),2) + power(mappedVector(1) - _pathInitial(1),2));
%Get distance from mapped vector to final vector
dMapped_Final = sqrt(power(_pathFinal(0) - mappedVector(0),2) + power(_pathFinal(1) - mappedVector(1),2));
%Get angle A = cos(A) = c^2 + a^2 - b^2 / 2*c*a
b_ang = acosd(power(dInitial_Mapped,2) + power(dMapped_Final,2) - power(dInitial_Final,2) / 2 * dInitial_Mapped * dInitial_Final);
Angle = 180 - 90 - b_ang
