-module(square).
-author({shinigami}).
-vsn(001).
-compile(export_all).


loop() ->
receive
    	{ rectangle, Width, Hit } ->
               io:format("arae of rectangle is ~p~n", [Width*Hit]),
               loop();
        { crircle, R} ->
               io:format("arae of crircle is ~p~n",[3.1415926*R*R]),
               loop();
        Other ->
               io:format("I don't know what the area of a ~p is ~n", [Other]),
               loop()
end.
