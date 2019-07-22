# ngl:meta
ngl:meta<ngc:matrix> meta_matrix
{
    ngl:branch
    {
        (meta.concept.size > 8000) { meta.concept.storage ngl:storage:dynamic }
        (meta.concept.storage ngl:storage:static)
    }
}