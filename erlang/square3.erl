-module(square3).
-author({shinigami}).
-vsn(001).
-compile(export_all).


st2art() ->
    spawn(fun loop/0).

area(Pid,What) ->
    rpc(Pid, What).

rpc(Pid,Request) ->
    Pid! {self(), Request},
    receive
        {Pid,Response} ->
            Response
    end.

loop() ->            
    receive
        {From, {retangle , Width,Hit}} ->
                From ! {self(),Width*Hit},
                loop();
        {From, {cricle, R}} ->
            From! {self(),3.1415926*R*R},
            loop();
        {From ,Other} ->
            From ! {self(),{error,Other}},
            loop()
    end.
