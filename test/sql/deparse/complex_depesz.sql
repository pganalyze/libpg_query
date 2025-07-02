SELECT
    decode(a.category, NULL, b.category, a.category) AS category,
    b.par AS "Total object Request", b.ps AS "objects Served",
    b.ar AS "Total sushi Request", a.sushis AS "sushis Served",
    round(decode(b.ar, 0, 0, (b.ar - decode(a.sushis, NULL, 0, a.sushis)::numeric) / b.ar) * 100, 3) AS "USR",
    a.clk AS points,
    decode(b.ps, 0, 0, round((a.clk / b.ps) * 100, 3)) AS "CTR", a.cpc AS "CPC",
    a.tc AS "Cost",
    decode(b.ps, 0, 0, (a.tc / b.ps) * 1000::numeric(8, 3)) AS effectcost
FROM
    (
        SELECT
            decode(b.category, NULL, 'N/A', b.category) AS category,
            sum(doughnuts) AS sushis, sum(points) AS clk,
            round(sum(total_cost)::numeric, 3) AS tc,
            decode(sum(points), 0, 0, round(sum(total_cost) / sum(points)::numeric, 3)) AS cpc
        FROM
            daily_city_dealer_summary a,
            category_dealer_map b
        WHERE
            a.category_dealer_id = b.category_dealer_id
            AND created_day BETWEEN '2010-05-01' AND '2010-05-25'
        GROUP BY b.category
    ) a
    FULL JOIN (
        SELECT
            decode(a.category, NULL, 'N/A', decode(a.category, '-', 'World-Remaining countries', a.category)) AS category,
            sum(valid_object_request) AS par, sum(valid_sushi_request) AS ar,
            sum(object_doughnuts) AS ps
        FROM traffic_hit a
        WHERE request_date BETWEEN '2010-05-01' AND '2010-05-25'
        GROUP BY a.category
    ) b ON lower(a.category) = lower(b.category)
ORDER BY 4 DESC
