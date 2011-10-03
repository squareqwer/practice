-module(example1).


-export([p1/1,
        total/1,
        sum/1,
        qsort/1,
        pythag/1,
        max/2,
        odds_and_evens/1,
        odds_and_evens_acc/1,
        odds_and_evens_acc/3,
        demo1/0,
        demo2/0,
        demo3/0]).

p1({point,X,Y})->
    X+Y.



cost(apple)->
io:format("apple~n"),
    1;
cost(banana) ->
io:format("banana~n"),
    2;
cost(book) ->
io:format("book~n"),
    3.

total([])->
    0;
total([{What,N}|T]) ->
cost(What)*N+total(T).           

sum(L)->
    sum(L,0).
sum([],N)->
    N;
sum([H|T],N) ->
    sum(T,H+N).


qsort([])->
    [];
qsort([Pivot|T]) ->
    qsort([X||X<-T,X<Pivot]) 
        ++[Pivot]++ 
        qsort([X||X<-T,X>=Pivot]).

%毕达哥拉斯三元组
pythag(N)->
    [{A,B,C}||
        A<-lists:seq(1,N),
        B<-lists:seq(1,N),
        C<-lists:seq(1,N),
        A+B+C=<N,
        A*A+B*B=:=C*C
].




%断言

max(X,Y) when X>Y,(X rem 3) =:=0 ->
    X;
max(X,Y) ->Y.


-record(todo,{status=reminder,who=joe,text}).


%累加器

odds_and_evens(L)->
    Odds = [X||X<-L,(X rem 2)=:=1],
    Evens = [X||X<-L,(X rem 2)=:=0],
    {Odds,Evens}.

odds_and_evens_acc(L)->
    odds_and_evens_acc(L,[],[]).

odds_and_evens_acc([H|T],Odds,Evens)->
case (H rem 2) of %%条件判断有点象switch 
    1 -> odds_and_evens_acc(T,[H|Odds],Evens);
        0 -> odds_and_evens_acc(T,Odds,[H|Evens])
                                    end;
odds_and_evens_acc([],Odds,Evens) ->
    {lists:reverse(Odds),lists:reverse(Evens)}.



%%异常

generate_execption(1)->
    a;
generate_execption(2) ->
    throw(a);
generate_execption(3) ->
    exit(a);
generate_execption(4) ->
    {'Exit',a};
generate_execption(5) ->
    erlang:error(a).

demo1()->
    [catcher(I)||I<-[1,2,3,4,5]].

catcher(N)->
        try generate_execption(N) of
            Val->{N,normal,Val}
        catch
            throw:X->{N,caught,thrown,X};
            exit:X ->{N,caught,exited,X};
            error:X ->{N,caught,error,X}
end.
    

demo2()->
    [{I,(catch generate_execption(I))} || I<-[1,2,3,4,5]].

%栈跟踪

demo3()->
    try generate_execption(5)
    catch
        eror:X->
            {X,erlang:get_stacktrace()}
    end.






%%erlang 宏

-define(DWORD ,32/unsigned-little-integer).
-define(LONG, 32/unsigned-little-integer).
-define(WORD, 16/unsigned-little-integer).
-define(BYTE, 8/unsigned-little-integer).)
