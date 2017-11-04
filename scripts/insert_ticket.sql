-- Function: ticket_insert(text, text)

-- DROP FUNCTION ticket_insert(text, text);

CREATE OR REPLACE FUNCTION ticket_insert(relname text,reljson text)
RETURNS void AS
$BODY$	
declare inputstring text;
BEGIN

	SELECT string_agg(quote_ident(key),',') 
	INTO inputstring 
	FROM json_object_keys(reljson::json) AS X (key);

	EXECUTE 'INSERT INTO '
	|| quote_ident(relname) 
	|| '(' || inputstring || ')'
	|| ' SELECT ' 
	|| inputstring 
	|| ' FROM json_populate_record'
	|| '( NULL::' || quote_ident(relname)
	|| ' , json_in($1))'
	USING reljson::cstring;

END;

$BODY$
LANGUAGE plpgsql VOLATILE
COST 100;
