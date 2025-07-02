CREATE TRIGGER query_runs_notify AFTER INSERT ON public.query_runs REFERENCING NEW TABLE rows EXECUTE FUNCTION public.query_runs_notify()
