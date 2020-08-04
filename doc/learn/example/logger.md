<logger>[<level> <date>]>

(the id <id> is invalid)

logger.set_format("%l %d");
log("id {} not found", id);

ngs:logger_a [<level> <date> <message>]

ngc:logger logger<ngs:logger_a>

logger.log<(is <id> not found)>