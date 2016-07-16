; ModuleID = '.k'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-f80:128:128-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32-S32"


; Type declares


; Global vars

declare i32 @sum(%i32 %a, %i32 %b) inlinehint 
declare i32 @mul(%i32 %a, %i32 %b) inlinehint 

; Funcs declares


; Implementation

define i32 @test(%i32 %a, %i32 %b, %i8 %c, %i1 %d) inlinehint x86_stdcallcc {
  %add.1 = add i32 2, 3
  %add.0 = add i32 %add.1, 4
  ret i32 %add.0
}

define void @proc() inlinehint {
  ret void
}


; Metadata
!0 = metadata !{ metadata !0 }
