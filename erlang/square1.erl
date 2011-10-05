-module(square1).
-author({shinigami}).
-vsn(001).
-compile(export_all).

rpc(Pid,Request) ->
    Pid! {self(), Request},
    receive
        Response ->
            Response
    end.

loop() ->            
    receive
        {From, {retangle , Width,Hit}} ->
                From ! Width*Hit,
                loop();
        {From, {cricle, R}} ->
            From! 3.1415926*R*R,
            loop();
        {From ,Other} ->
            From ! {error,Other},
            loop()
    end.

