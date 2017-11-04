--update bill set  caller_id=to_number(caller,'999999999999999999')  where caller_id is null;
--update bill set caller_id=caller_id-380000000000 where caller_id >380000000000 and caller_id<381000000000;
--update bill set called_id=called_id-380000000000 where called_id >380000000000 and called_id<381000000000;
update bill set called_id=0-called_id where char_length(called)>18;
