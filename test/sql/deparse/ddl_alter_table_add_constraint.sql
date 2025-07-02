ALTER TABLE ONLY public.vacuum_insight_runs_7d
    ADD CONSTRAINT vacuum_insight_runs_7d_pkey PRIMARY KEY (server_id, check_name, run_at)
