/*
 *  Copyright 2018 by Leander Beernaert (lbb-dev@pm.me)
 *
 *  This file is part of YAL.
 *
 *  YAL is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, either version 3
 *  of the License, or (at your option) any later version.
 *
 *  YAL is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with YAL. If not, see <http://www.gnu.org/licenses/>.
 */


#include "fixture.h"

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


class General : public CompileFixture {

};

TEST_F(General, StructAccess) {
    const char* input =
R"R(
    type Bar : struct {
        x : i32
    }

    type Foo : struct {
        b: Bar
    }

    fn Foo::Static(x:i32) {

    }

    fn Foo::instance(&self) : bool {
        return self.b.x == 20;
    }

    fn Foo::setX(mut& self, newX:i32) {
        self.b.x = newX;
    }

    fn other(x: mut Foo) {
        var z:i32 = x.b.x;
    }

    fn main() {
        var f:mut Foo = Foo{b:Bar{x:20}};
        f.b = Bar { x:10};
        f.setX(40);

        other(f);
    }
)R";
    compile(input,"general/structaccess.yal");
    EXPECT_FALSE(m_errorReporter.hasErrors());
}


TEST_F(General, RefTest) {
    const char* input =
R"R(
    type Bar : struct {
        x : i32
    }


    type Foo : struct {
        b: mut Bar
    }



    fn test(f: mut& Foo) {
        f.b = Bar { x: 30 };
    }

    fn assign(f: mut& Foo) {
       // Should not be allowed
       //f = Foo{b:Bar{x:20}};
    }


    fn Foo::create(i:i32) : mut Foo{
        return Foo { b:Bar{ x:i}};
    }

    fn moveHere(f:mut Foo) {

    }

    fn move(f:mut Foo) {
      test(&f);
      moveHere(f);
    }

    fn Foo::createWithBar(b: mut Bar) : mut Foo{
        return Foo { b:b};
    }

    fn main() {
       var f:mut Foo = Foo{b:Bar{x:20}};
       test(&f);
       f.b = Bar { x:10};

       var f2:Foo = Foo::create(30);
       var o:&Foo = &f2;

       move(f);
       var other:mut Bar = Bar { x: 20 };
       f = Foo::createWithBar(other);
    }
)R";
    compile(input,"general/reftest.yal");
    EXPECT_FALSE(m_errorReporter.hasErrors());
}